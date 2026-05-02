# Welcome to Ares CAN Library!

Hi! This is the custom CAN communication library for RSX Science, written by Kevin Caldwell and Vhea He (2026). Our library is named after Ares, the Greek god of War. Ares is another name for Mars, the Red Planet our rover is designed to explore. The library is designed to facilitate CAN message transmission between a Raspberry Pi 4/5 and multiple Arduino Nano based modules over a central CAN Bus. It contains two major packages to be installed: `RSX_Arduino` and `RSX_Python`.

The Controller Area Network (CAN) is a standardized communication protocol that enables microcontrollers and devices to communicate with each other in real-time without needing a host computer. Designed for reliability and efficiency, it ensures seamless communication in critical systems. This was chosen for the rover for its modular and reliable properties. Read more about CAN [here](https://unstop.com/blog/what-is-can-protocol).

# Ares Library Installation

### Arduino

The custom CAN functions made for RSX Science's Arduino based modules can be accessed in the `ares_can_lib/rsx_arduino` directory. It is recommended to import this as a library when working on CAN communication software for ease of access to functions.

This library contains a variety of useful functions and a custom class designed to read and send messages easily between RSX Science modules. This library should be used in conjunction with the `RSX_Python` package that comes with this library in order to communicate with the Raspberry Pi.

To install and use the `RSX_Arduino` package, follow these steps:

 1. Visit the `ares_can_lib/rsx_arduino` directory in the repository.
 2. Copy the folder inside named `science_can` into the "Libraries" folder created by your Arduino IDE. Usually, the address for this would be:
	- **Windows:** `C:\Users\{username}\Documents\Arduino`
	- **macOS:** `/Users/{username}/Documents/Arduino`
	- **Linux:** `/home/{username}/Arduino`
 3. To use in a sketch (`ino` file), go to "Sketch >> Include Library >> `science_can`", and it should add the appropriate header file to your sketch. If this does not happen, try restarting the Arduino IDE.
 4. Have fun! Use the functions you need to send your own CAN messages!

### Python

The Python package contains CAN functions made for the RSX Science Raspberry Pi, containing functions that allow communications between the ground station and the rest of the science module.

To use this library, follow these steps:

 1. Visit the `ares_can_lib/rsx_python` directory in the repository.
 2. Copy the folder into the root directory of your workspace.
 3. Run your python script as a module in order to use the functions in the library. You can run a sample test with the command: `python3 -m functional_tests.servo_spin_test.servo_spin_test`.
 4. Have fun! Use the functions you need to send your own CAN messages!

## Usage

The Ares library uses a ScienceCANPacket as an intermediate layer
with fields representing the different parts of

### Ur Mom
Your mother would be proud of all you accomplished. By using this library, you CAN do anything!
