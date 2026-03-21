# Enables RPi to send a series of sanity pulses
# Able to be recieved by arduino

import can
from science_can import *
from CAN_utilities import initialize_bus
# from CAN_utilities import generate_can_id, initialize_bus, CMD_API_NONRIO_HB

# Instantiate CAN bus
BUS = initialize_bus()

while True:
  can_msg = BUS.recv()
  # print("baby u don't know what hit you woooaah")
  if can_msg == None:
    print("NUTTHIN YET CHIEF BEEF")
  else:
    scp = assemble_SCP_from_frame(can_msg)
    a = scp.data[0]
    scp.dlc = 8
    print()
    print(f"RECEIVED: {hex(scp.data[0])}, {hex(scp.data[1])}, {hex(scp.data[2])}, {hex(scp.data[3])}, {hex(scp.data[4])}, {hex(scp.data[5])}, {hex(scp.data[6])}, {hex(scp.data[7])}")
    for i in range(8):
      scp.data[i] = a+1
    pulse_pkg = assemble_frame_from_SCP(scp)
    BUS.send(pulse_pkg)
    print("there's stuff in here")
    print(can_msg)

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