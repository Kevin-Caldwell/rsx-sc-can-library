# Enables RPi to send a series spin commands to a servo over CAN
# Able to be recieved by arduino

from ares_can_lib.rsx_python.science_can import *
from ares_can_lib.rsx_python.CAN_utilities import initialize_bus

# Instantiate CAN bus
BUS = initialize_bus()

# Example ScienceCanPacket to dissect
multipacket_request = ScienceCanPacket()

multipacket_request.priority = 0
multipacket_request.multipacket_id = assign_available_slot()
multipacket_request.sender = SCI_MODULE_RPI
multipacket_request.receiver = SCI_MODULE_MULTISPECTRAL
multipacket_request.peripheral = SCI_PERIPHERAL_NONE
multipacket_request.extra = SCI_ERROR_SUCCESS
multipacket_request.dlc = 8
multipacket_request.data = bytes([0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF])

TX_BUFFER.append(multipacket_request)
process_tx(BUS)

import time
while (True):
    # We are in the loop!
    msg_received = ScienceCanPacket()
    process_rx(BUS)

    if MULTIPACKET_BUFFER == []:
        continue
    else:
        for scp_set in MULTIPACKET_BUFFER:
            for scp in scp_set:
                scp.print_pkt()
    if RX_BUFFER == []:
        continue
    else:
        print(RX_BUFFER)
        for msg in RX_BUFFER:
            msg_received = msg
            if type(msg_received) == list:
                msg_received[0].print_pkt()
                combined_data = combine_multipacket_data(msg_received)
                print(f"All Multipacket Data: {combined_data}")
            else:
                print(f"Length of RX_BUFFER: {len(RX_BUFFER)}")
                msg_received.print_processed_pkt()
    # pulse_pkg.data = bytes([(pulse_pkg.data[0] + 1) % 18, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF])
    # pulse = assemble_frame_from_SCP(rsx_sci_pkt=pulse_pkg)
    # task = BUS.send(pulse)
    time.sleep(1)