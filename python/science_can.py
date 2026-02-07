# MAIN PYTHON FILE FOR RSX SCIENCE 

# Contains all the main science sensors and modules for CAN communication
# 2026/26 edition  

from enum import ENUM

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

class RSX_Science_CAN_Message:
    sender_device = None # Device from which message is sent from
    science_module = None # Science module message pertains to
    science_sensor = None # Science sensor message applies to
    command = "" # Command being sent in the message 
    error = 0

    def send_msg(immediate=True):
        print ("ur mum fat")
        print("ive been doing this all day is python just my life now")
        print("I can tell people I work with snakes and chips :/")
        print("painge")
        print("kekw (>:())\npoggers\nPOG")

    def receive_msg():
        print ("who are you who are so wise in the ways of science")

    def parse_CAN_msg(msg):
        print("we comrade")



