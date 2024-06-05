# Ocean Cleanup Remotely Operated Vehicle Firmware
*Team Members: Matthew Armstrong, William Fitzgerald, Jake Gustafson, and Amy Law*

Allows a PSOC 6 microcontroller to operate thrust and servo motors, collect data from ultrasonic and GPS sensors, and facilitate data transfer over Bluetooth Low Energy (BLE) to control a vehicle for ocean cleanup. Check out our iOS application [here](https://github.com/matthewarmstr/ocean-cleanup-app). 

This project was developed as part of our UC Davis ECS 193 Senior Design Project in coordination with an EEC 136 design team. Special thanks to Professor Christopher Nitta and Teaching Assistant Ajay Suresh for their guidance and support throughout the project.

## Firmware Overview
The microcontroller operates the thrust and servo motors using pulse width modulation (PWM), allowing them to be operated at specific speeds/positions as desired.

The connected ultrasonic reads the distance between itself and an oncoming object. The microcontroller sends a 15µS pulse every 300ms to the ultrasonic's TRIG input. This enables the sensor to send an ultrasonic frequency that bounces off an object and returns to the sensor. The sensor sends a signal back to the microcontroller when it first sends out the frequency, starting a timer to keep track of the pulse width. Upon receiving the frequency again, the sensor sends a second signal back. At this point, the microcontroller stops the timer and saves the pulse width in microseconds representing how far away an oncoming object is. 

The GPS module sends its latitude and longitude data in NMEA format (see the documentation for this format [here](https://w3.cs.jmu.edu/bernstdh/web/common/help/nmea-sentences.php)) to the microcontroller every second over a dedicated UART connection. 

The data from the ultrasonic and GPS modules are then stored in the Bluetooth Low Energy (BLE) stack for access by a wirelessly connected device.

To give the user precise control over the vehicle's movement, an encoding scheme was developed for one of the Bluetooth characteristics. The encoding structure is as follows (going from least significant to most significant bits):
- Left (when high, rotate the rudder to allow the vehicle to move left)
- Right (when high, rotate the rudder to allow the vehicle to move right)
- Trash (when high, open/close the trash gate)
- Forward (when high, activate thrust motor)
- [Bits 4-7 are unused for additional functionality]

When new controls are received, the microcontroller updates the PWM values according to the predefined motor positions the user desires to control. Each time the microcontroller's Bluetooth stack goes into a disconnected state (whether on an intentional disconnect by the user, an out-of-range error, or a dropped connection) the controls are automatically reset to their default positions (thrust off, rudder straight, etc.). This ensures the vehicle's controls remain stable when an unexpected error occurs.

## Prerequisites
1. Download and install [PSOC Creator](https://www.infineon.com/cms/en/design-support/tools/sdk/psoc-software/psoc-creator/) *(developed using PSOC Creator 4.4)*.

## Required Components for Sensing, Controls, and Power
1. [PSOC 6 BLE Prototyping Kit](https://www.infineon.com/cms/en/product/evaluation-boards/cy8cproto-063-ble/)
2. [RCWL-1601 Ultrasonic Sensor](https://www.adafruit.com/product/4007)
3. [GT-U7 GPS Module with Antenna](https://www.amazon.com/dp/B07PRGBLX7)
4. [Underwater Thrust Motor (12-16V)](https://www.underwaterthruster.com/products/apisqueen-u2-mini-1-3kg-underwaterthruster-thruster-16v-130w)
5. [Brushless Motor Electric Speed Controller (ESC)](https://www.rcelectricparts.com/40a-esc---classic-series.html)
6. [Waterproof 20KG Servo Motor (x2)](https://www.amazon.com/Miuzei-Torque-Digital-Waterproof-Control/dp/B07HNTKSZT)
7. [Buck-Boost Converter (3-16V input, 2.5-9V or 3.3/5V output)](https://www.sparkfun.com/products/15208)
8. [9V Alkaline Battery](https://www.amazon.com/Duracell-MN1604B2Z-Alkaline-General-Purpose/dp/B00PV1EIX8)
9. [11.1V LiPo 1400mAh Battery](https://www.amazon.com/Connector-Airplane-Helicopter-Quadcopter-Multi-Motor/dp/B07L6BNTDV)
10. [Waterproof Box with Cable Holders](https://www.amazon.com/Joinfworld-Outdoor-Extension-Cord-Cover/dp/B0CKZ34N8L)

## Vehicle Hardware Architecture
![Ocean Cleanup Vehicle Hardware Architecture](https://github.com/matthewarmstr/ocean-cleanup-rov-controls.cydsn/assets/130258852/dc35302b-5c96-4135-975f-5ab1fb547196)

## Installation
1. Clone this repository.
2. Open PSOC Creator and navigate to File > Open > Project/Workspace.
3. Locate the project repository folder on your computer and select `ocean-cleanup-rov-controls.cyprj`.

## Deployment Instructions
Connect your PSOC 6 with the included cable. In PSOC Creator, click `Program` on the upper-left toolbar and select the `cm0p` core on the device from the toolbar, then connect. The project will be compiled before the microcontroller is flashed (this may take a few minutes).

In the workspace explorer, click on `Pins` under `Design Wide Resources`. Connect the thrust motor (using the ESC), servo motors, and sensors to the appropriate GPIO pins as shown in the displayed pin layout diagram.

***Note: all power and logic that enters and exits the microcontroller must be 3.3V. Sending 5V to a GPIO pin may damage the PSOC 6 microcontroller. All components that supply power and logic to our PSOC 6 use only 3.3V.***

To give individual vehicles uniquely identifiable Bluetooth names, open `TopDesign.cysch`. Double-click on the BLE module, and click on the `GAP Settings` tab. Change the `Device Name` field as desired. Click `Apply` and `OK`, then reprogram the microcontroller. Once the firmware has been flashed, repeat the process for each vehicle's PSOC 6 microcontroller. 
