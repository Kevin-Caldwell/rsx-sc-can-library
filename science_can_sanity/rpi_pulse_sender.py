# Enables RPi to send a series of sanity pulses
# Able to be recieved by arduino 

import can
from science_can import *
from CAN_utilities import initialize_bus
# from CAN_utilities import generate_can_id, initialize_bus, CMD_API_NONRIO_HB

# Instantiate CAN bus
BUS = initialize_bus()

# Example ScienceCanPacket to dissect 
pulse_pkg = ScienceCanPacket()

pulse_pkg.priority = 0
pulse_pkg.science = 0
pulse_pkg.sender = Module.SCI_RPI
pulse_pkg.receiver = Module.SCI_DRILL
pulse_pkg.sensor = Sensor.SCI_SERVO
pulse_pkg.extra = Error.SCI_SUCCESS
pulse_pkg.dlc = 8
pulse_pkg.data = bytes([0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF])

pulse = assemble_frame_from_SCP(rsx_sci_pkt=pulse_pkg)

# global BUS

print("We got here")

task = BUS.send_periodic(pulse, 0.01, store_task= False)
print("Pulse signal initiated")

while True:
    pass