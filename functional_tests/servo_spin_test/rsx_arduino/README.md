# Move Servo Test

> The Circular Buffer still has not been tested, and
> may be a source of error.

## Arduino Settings
Assuming Drill CAN module (0x4), Servo Sensor (0x3). 

## Printing

To help debug CAN messages, I have added functionality
for displaying every CAN message that enters the buffer, 
or only displaying the raw format of CAN messages
that have been filtered out.

