# Enables RPi to send a series of sanity pulses
# Able to be recieved by arduino

import can
from science_can import *
from CAN_utilities import initialize_bus
# from CAN_utilities import generate_can_id, initialize_bus, CMD_API_NONRIO_HB

# Instantiate CAN bus
BUS = initialize_bus()

# Set our current device to be the RPi
CURRENT_CAN_MODULE = Module.SCI_RPI

print("WOW THIS IS A TEST")
get_module_name(Module.SCI_RPI)

# Constant looping 
while True:

  # Try to receive a can message from the BUS
  can_msg = BUS.recv()
  # print("baby u don't know what hit you woooaah")

  # If a CAN message is received, we want to read it
  if can_msg != None:
    # Extract the CAN message and fill out an SCP 
    scp = assemble_SCP_from_frame(can_msg)

    # Check if the message was meant for this device 
    if scp.receiver == CURRENT_CAN_MODULE:

      a = scp.data[0]
      # scp.dlc = 8

      # Print the received message 
      print(f"RECEIVED: {hex(scp.data[0])}, {hex(scp.data[1])}, {hex(scp.data[2])}, {hex(scp.data[3])}, {hex(scp.data[4])}, {hex(scp.data[5])}, {hex(scp.data[6])}, {hex(scp.data[7])}")
      
      # Increment to update the data
      for i in range(8):
        scp.data[i] = a+1
    
      # Change the address to be sending from the RPi 
      scp.sender = CURRENT_CAN_MODULE
      scp.receiver = Module.SCI_DRILL

      # Prepare CAN message to be sent out 
      pulse_pkg = assemble_frame_from_SCP(scp)
      BUS.send(pulse_pkg)
      print("there's stuff in here")
      print(can_msg)

  # If the can message is empty, keep waiting 
  else:
    print("NUTTIN YET CHIEF BEEF!!")

print(can_msg)

pulse_pkg = assemble_SCP_from_frame(can_frame=can_msg)
print(f"CAN Priority: {hex(pulse_pkg.priority)}")
print(f"CAN Science: {pulse_pkg.science}")
print(f"CAN Sender: {pulse_pkg.sender}")
print(f"CAN Receiver: {pulse_pkg.receiver}")
print(f"CAN Sensor: {pulse_pkg.sensor}")
print(f"CAN Extra: {pulse_pkg.extra}")
print(f"CAN DLC: {pulse_pkg.dlc}")
print("CAN Data: ", end='')
for i in range(8):
  print(hex(pulse_pkg.data[i]).upper(), end=',')

# print(f"CAN Data: {hex(pulse_pkg.data)}")

print()
BUS.shutdown()