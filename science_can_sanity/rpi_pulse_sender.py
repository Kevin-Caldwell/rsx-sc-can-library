# Enables RPi to send a series of sanity pulses
# Able to be recieved by arduino 

import can
from python.science_can import *
from python.CAN_utilities import initialize_bus
# from CAN_utilities import generate_can_id, initialize_bus, CMD_API_NONRIO_HB

# Instantiate CAN bus
BUS = initialize_bus()

# Example ScienceCanPacket to dissect 
pulse_pkg = ScienceCanPacket()

pulse_pkg.priority = 0
pulse_pkg.science = 0
pulse_pkg.sender = SCI_MODULE_RPI
pulse_pkg.receiver = SCI_MODULE_DRILL
pulse_pkg.sensor = SCI_SENSOR_SERVO
pulse_pkg.extra = SCI_ERROR_SUCCESS
pulse_pkg.dlc = 8
pulse_pkg.data = bytes([0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF])

pulse = assemble_frame_from_SCP(rsx_sci_pkt=pulse_pkg)

# global BUS

print("We got here")

task = BUS.send_periodic(pulse, 0.01, store_task= False)
print("Pulse signal initiated")

while True:
    pass