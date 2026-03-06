import can
from python.science_can import *
from CAN_utilities import initialize_bus
# from CAN_utilities import generate_can_id, initialize_bus, CMD_API_NONRIO_HB

# Instantiate CAN bus
BUS = initialize_bus()

# Example ScienceCanPacket to dissect 
pulse_pkg = ScienceCanPacket(
    priority = 0,
    science = 0,
    sender = SCI_MODULE_RPI,
    receiver = SCI_MODULE_DRILL,
    sensor = SCI_SENSOR_SERVO,
    extra = SCI_ERROR_SUCCESS,
    dlc = 8,
    data = bytes([0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF])
)

pulse = can.Message()

pulse = assemble_frame_from_SCP(can_frame=pulse, rsx_sci_pkt=pulse_pkg)

# global BUS

task = BUS.send_periodic(pulse, 0.01, store_task= False)
print("Pulse signal initiated")

while True:
    pass