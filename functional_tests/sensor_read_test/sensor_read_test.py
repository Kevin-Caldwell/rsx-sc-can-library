# Enables RPi to send a series spin commands to a servo over CAN
# Able to be recieved by arduino

from ares_can_lib.rsx_python.science_can import *
from ares_can_lib.rsx_python.CAN_utilities import initialize_bus

# Instantiate CAN bus
BUS = initialize_bus()

import time
while (True):
    msg_received = ScienceCanPacket()
    process_rx(BUS)
    if RX_BUFFER == []:
        continue
    else:
        print(RX_BUFFER)
        for msg in RX_BUFFER:
            msg_received = msg
            if type(msg_received) == list:
                print("we can't really deal with that sorry")
            else:
                print(f"Length of RX_BUFFER: {len(RX_BUFFER)}")
                msg_received.print_processed_pkt()

        RX_BUFFER.clear()