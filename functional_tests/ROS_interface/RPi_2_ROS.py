# Contents of this script sends SCP Messages from RPi back to Ground Station through ROS
# Communicates contents from CAN data through ROS

import rclpy
from rclpy.node import Node
from ares_can_lib.rsx_python.science_can import *
from ares_can_lib.rsx_python.CAN_utilities import initialize_bus
import numpy as np
import time

from science.msg import SCP

# Link from RPi to ROS, where Pi sends SCP messages back with ROS
class RPi_2_ROS_Link(Node):

    def __init__(self):
        super().__init__('ros_sender')
        
        self.publisher = self.create_publisher(
            SCP,
            "SCP_receive", 
            10
        )

        self.send = True
        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback, autostart= True)
        self.index = 0
        
    def ros_sender_push(self):
        
        # Fill up ROS topic with info from SCP 
        for packet in RX_BUFFER:
            msg = send_ROS_topic()

            # Send msg back to ground station over ROS
            if self.send:
                self.publisher.publish(msg)

def main():
    # Instantiate CAN bus
    BUS = initialize_bus()

    # Create instance of ROS sender 
    sender = RPi_2_ROS_Link()
    
    while (True):
        process_rx(BUS)
        sender.ros_sender_push()
        time.sleep(1)
        
if __name__ == "__main__": 
    main()