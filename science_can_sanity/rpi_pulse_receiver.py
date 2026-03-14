# Enables RPi to send a series of sanity pulses
# Able to be recieved by arduino 

import can
from python.science_can import *
from python.CAN_utilities import initialize_bus
# from CAN_utilities import generate_can_id, initialize_bus, CMD_API_NONRIO_HB

# Instantiate CAN bus
BUS = initialize_bus()

can_msg = BUS.recv()

print(can_msg)

pulse_pkg = assemble_SCP_from_frame(can_frame=can_msg)

print()