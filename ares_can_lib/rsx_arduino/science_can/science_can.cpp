#include "science_can.h"

#include "devices/can_config.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

namespace Science {
namespace MPM {

constexpr int kMaxMultiPacket = 15;
constexpr int kFrameIndexBits = 12;
constexpr int kMaxLength = (1 << (kFrameIndexBits + 1));
constexpr int kOneShotLength = 8; // 8 Bytes
constexpr int kMaxStoredPacket = 1;

static BufferInfo sample_extraction_buffer;

struct ResourceState {
  // Data
  uint8_t* base_;
  uint8_t* pos_;
  uint16_t len_;

  // CAN
  module_t other_; // Sender / Receiver
  peripherals_t peripheral_;

  // Table
#if !defined(STRIPPED_CAN)
  bool available_;
#endif
  uint8_t mapped_index_;
};

#if defined(STRIPPED_MPM)
static ResourceState send_table;
#else
struct ResourceTable {
public:
  ResourceTable()
  {
    begin_ = &arr_[0];
    end_ = &arr_[kMaxStoredPacket];
  }

  ResourceState* alloc(const uint8_t* base,
    const uint8_t len,
    const int frame_index)
  {
    assert(len < kMaxLength &&
      "Trying to allocate longer than Max Length");
    assert(frame_index < kMaxMultiPacket &&
      "More frames than possible to allocate");

    ResourceState* resource = begin_;
    while (resource->available_ == 0 && resource != end_) {
      resource++;
    }
    assert(resource != end_ && "Table full");
    resource->available_ = 0;
    return resource;
  }

  int free(const int frame_index)
  {
    assert(frame_index < kMaxMultiPacket &&
      "Trying to access out of bounds frame");

    ResourceState* resource = begin_;
    while(resource->mapped_index_ != frame_index && resource != end_) {
      resource++;
    }
    assert(resource != end_ && "Frame not found");

    resource->base_ = nullptr;
    resource->len_ = 0;
    resource->pos_ = nullptr;
    resource->other_ = kModuleNone;
    resource->peripheral_ = kPeripheralNone;
    resource->available_ = 1;
    resource->mapped_index_ = -1;
    return 0;
  }

  ResourceState* get(const int frame_index)
  {
    assert(frame_index < kMaxMultiPacket &&
      "Trying to access out of bounds frame");

    ResourceState* resource = begin_;
    while (resource->mapped_index_ != frame_index && resource != end_) {
      resource++;
    }
    assert(resource != end_ && "Frame not found");
    return resource;
  }

  // Called by Sender
  ScienceCANMessage getNextCAN(const int frame_index)
  {
    ResourceState* resource = get(frame_index);
    ScienceCANMessage message;

    const int sent_progress = resource->pos_ - resource->base_;
    const int remaining = resource->len_ - sent_progress;
    message.priority_ = 1;
    message.multipacket_id_ = frame_index;
    message.sender_ = CAN_MODULE;
    message.receiver_ = resource->other_;
    message.peripheral_ = resource->peripheral_;
    message.dlc_ = MIN(remaining, kOneShotLength);
    if (remaining) {
      message.extra_ = sent_progress / 8;
      for (int i = 0; i < message.dlc_; ++i) {
        message.data_[i] = resource->pos_++;
      }
    } else {
      message.extra_ = -1; // Send END signal
    }

    return message;
  }

  void setNextCAN(ScienceCANMessage message)
  {
    const int frame_index = message.multipacket_id_;
    ResourceState* resource = get(frame_index);
    uint8_t* ptr = resource->base_ + message.extra_ * 2;
    for (int i = 0; i < message.dlc_; ++i) {
      *ptr++ = message.data_[i];
    }

  }

private:
  ResourceState arr_[kMaxStoredPacket];
  const ResourceState* begin_;
  const ResourceState* end_;

};

static ResourceTable send_table;
#endif

bool queue_send = false;
int frame = -1;

}

CANBuffer rx_buffer;
CANBuffer tx_buffer;

MCP2515 mcp2515(CS_PIN);

void can_setup() {
  SPI.begin();
  mcp2515.reset();
  Serial.println("MCP2515 init OK YAY! :)");
}

void parse_can_message(const can_frame& frame,
                       ScienceCANMessage* message) {
  uint32_t can_id = frame.can_id;
  message->extra_ = can_id & 0xFFF;
  can_id >>= 12;
  message->peripheral_ = can_id & 0xF;
  can_id >>= 4;
  message->receiver_ = can_id & 0xF;
  can_id >>= 4;
  message->sender_ = can_id & 0xF;
  can_id >>= 4;
  message->multipacket_id_ = can_id & 0xF;
  can_id >>= 4;
  message->priority_ = can_id & 0x1;
  message->dlc_ = frame.can_dlc;

#if !defined(STRIPPED_CAN)
#pragma loop unroll 8
#endif
  for (int i = 0; i < 8; ++i) {
    message->data_[i] = frame.data[i];
  }
}

void to_can_frame(const ScienceCANMessage* message,
                  can_frame* frame) {
  uint32_t can_id = 0b1000;
  can_id |= message->priority_ & 0x1;
  can_id <<= 4;
  can_id |= message->multipacket_id_ & 0xF;
  can_id <<= 4;
  can_id |= message->sender_ & 0xF;
  can_id <<= 4;
  can_id |= message->receiver_ & 0xF;
  can_id <<= 4;
  can_id |= message->peripheral_ & 0xF;
  can_id <<= 12;
  can_id |= message->extra_ & 0xFFF;

  frame->can_id = can_id;
  frame->can_dlc = message->dlc_;

#if !defined(STRIPPED_CAN)
#pragma loop unroll 8
#endif
  for (int i = 0; i < 8; ++i) {
    frame->data[i] = message->data_[i];
  }
}

// POTATERS ARE YUMMY

int process_rx() {

  int recv = false;
  struct can_frame rx_can_frame;

  for (int i = 0; i < MAX_RX; ++i) {
    MCP2515::ERROR res = mcp2515.readMessage(&rx_can_frame);
    if (res == MCP2515::ERROR_NOMSG || res == MCP2515::ERROR_FAIL) {
      break;
    }

#if defined(PRINT_ALL_CAN)
    Serial.print("ID: ");
    Serial.print(rx_can_frame.can_id, HEX);
    Serial.print(", Data: ");
    for (int i = 0; i < rx_can_frame.can_dlc; i++) {
      Serial.print(rx_can_frame.data[i]);
      Serial.print(", ");
    }
    Serial.println();
#endif

    ScienceCANMessage buf;

    parse_can_message(rx_can_frame, &buf);
    if (buf.receiver_ == CAN_MODULE) {
#if defined(PRINT_FILTERED_CAN)
      Serial.println("Received CAN message:");
      Serial.print("Priority: ");
      Serial.println(buf.priority_, HEX);
      Serial.print("Sender: ");
      Serial.println(buf.sender_, HEX);
      Serial.print("Receiver: ");
      Serial.println(buf.receiver_, HEX);
      Serial.print("Peripheral: ");
      Serial.println(buf.peripheral_, HEX);
      Serial.print("Extra: ");
      Serial.println(buf.extra_, HEX);
      Serial.print("DLC: ");
      Serial.println(buf.dlc_, HEX);
      Serial.print("Data: ");
      for (int i = 0; i < buf.dlc_; i++) {
        Serial.print(buf.data_[i], HEX);
        Serial.print(", ");
      }
      Serial.println("\n End CAN Message.");
#endif
      if (~buf.multipacket_id_) {
        rx_buffer.push(buf);
      } else {
        MPM::queue_send = true;
        MPM::frame = buf.multipacket_id_;
      }
      recv++;
    }
  }
  return recv;
}

int process_tx() {
  if (MPM::queue_send) {
    if (MPM::sample_extraction_buffer.available) {
      MPM::queue_send = false;
#if defined(STRIPPED_MPM)
      MPM::send_table.base_ = MPM::sample_extraction_buffer.base_;
      MPM::send_table.pos_ = MPM::sample_extraction_buffer.base_;
      MPM::send_table.len_ = MPM::sample_extraction_buffer.len_;
      MPM::send_table.mapped_index_ = MPM::frame;
#else
      MPM::send_table.alloc(MPM::sample_extraction_buffer.base_,
        MPM::sample_extraction_buffer.len_,
        MPM::frame);
#endif
    }
  }

  int cnt = 0;

  while (!tx_buffer.empty()) {
    const ScienceCANMessage buf = tx_buffer.last();
    struct can_frame tx_frame;
    to_can_frame(&buf, &tx_frame);
    if (~mcp2515.sendMessage(&tx_frame)) {
      tx_buffer.pop();
      cnt++;
    }
  }

  return cnt;
}

};  // namespace Science
