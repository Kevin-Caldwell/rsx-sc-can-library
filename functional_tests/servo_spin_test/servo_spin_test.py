# Enables RPi to send a series spin commands to a servo over CAN
# Able to be recieved by arduino

from rsx_science_can_lib.rsx_python.science_can import *
from rsx_science_can_lib.rsx_python.CAN_utilities import initialize_bus

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
pulse_pkg.data = bytes([0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF])

pulse = assemble_frame_from_SCP(rsx_sci_pkt=pulse_pkg)

import time
while (True):
    pulse_pkg.data = bytes([(pulse_pkg.data[0] + 1) % 18, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF])
    pulse = assemble_frame_from_SCP(rsx_sci_pkt=pulse_pkg)
    task = BUS.send(pulse)
    time.sleep(1)