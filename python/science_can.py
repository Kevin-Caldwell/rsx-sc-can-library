# MAIN PYTHON FILE FOR RSX SCIENCE 

# Contains all the main science sensors and modules for CAN communication
# 2026/26 edition  

from enum import ENUM
import can
from CAN_utilities import *
from science_can import *

# Types of modules
SCI_MODULE_NONE = 0 # No type
SCI_MODULE_RPI = 1 # Raspberry Pi 5 
SCI_MODULE_GENERAL = 2 # Arduino Nano
SCI_MODULE_OPTICS = 3 # Arduino Nano
SCI_MODULE_DRILL = 4 # Arduino Nano
SCI_MODULE_MOTOR = 5 # Arduino Nano

# Types of sensors 
SCI_SENSOR_NONE = 0 
SCI_SENSOR_ALL = 1
SCI_SENSOR_UVLED = 2
SCI_SENSOR_SERVO = 3
SCI_SENSOR_LINEAR_ACTUATOR = 4 
SCI_SENSOR_ULTRASONIC = 5
SCI_SENSOR_ELECTROMAGNET = 6
SCI_SENSOR_SPARK_MOTOR = 7 

# Types of errors 
SCI_ERROR_SUCCESS = 0 # No Error 
SCI_ERROR_GENERIC = 1 # General Error Msg 
SCI_ERROR_PP = 2

class ScienceCanPacket:
    priority: int = 0
    science: int = 0
    sender: int = 0
    receiver: int = 0
    sensor: int = 0
    extra: int = 0
    dlc: int = 0 
    data = [None, None, None, None, None, None, None, None]

    def send_msg(self, immediate=True):
        print ("ur mum fat")
        print("ive been doing this all day is python just my life now")
        print("I can tell people I work with snakes and chips :/")
        print("painge")
        print("kekw (>:())\npoggers\nPOG")

    def receive_msg():
        print ("who are you who are so wise in the ways of science")

    def parse_CAN_msg(msg):
        print("we comrade")

def assemble_SCP_from_frame(can_frame: can.Message, rsx_sci_pkt: ScienceCanPacket):
    # Fill the RSX_Sci packet with information from the CAN frame address
    can_id  = can_frame.arbitration_id
    rsx_sci_pkt.extra  = can_id & 0xFFF
    can_id = can_id >> 12
    rsx_sci_pkt.sensor     = can_id & 0xF
    can_id = can_id >> 4
    rsx_sci_pkt.receiver     = can_id & 0xF
    can_id = can_id >> 4
    rsx_sci_pkt.sender     = can_id & 0xF
    can_id = can_id >> 4
    rsx_sci_pkt.science     = can_id & 0xF
    can_id = can_id >> 4
    rsx_sci_pkt.priority     = can_id & 0x1

    # Assign the length 
    rsx_sci_pkt.dlc = can_frame.dlc

    # Fill the RSX_Sci packet with data received 
    for i in range (can_frame.dlc):
        rsx_sci_pkt.data[i] = can_frame.data[i]
    return 1

def assemble_frame_from_SCP(rsx_sci_pkt: ScienceCanPacket, can_frame: can.Message):
    # Initialize can_id for new frame to send
    can_id = 0

    # Populate can_id with info from RSX_Sci packet
    can_id |= rsx_sci_pkt.priority & 0x1
    can_id = can_id >> 4
    can_id |= rsx_sci_pkt.science & 0xF
    can_id = can_id >> 4
    can_id |= rsx_sci_pkt.sender & 0xF
    can_id = can_id >> 4
    can_id |= rsx_sci_pkt.receiver & 0xF
    can_id = can_id >> 4
    can_id |= rsx_sci_pkt.sensor & 0xF
    can_id = can_id >> 12
    can_id |= rsx_sci_pkt.extra & 0xFFF

    can_frame.arbitration_id = can_id

    can_frame.dlc = rsx_sci_pkt.dlc 

    return 1
    
def process_can_rx():
    return "bruh"
