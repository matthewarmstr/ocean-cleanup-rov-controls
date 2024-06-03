# Ocean Cleanup Remotely Operated Vehicle Firmware
*Team Members: Matthew Armstrong, William Fitzgerald, Jake Gustafson, and Amy Law*

Allows a PSoC™ 6 microcontroller to operate the motors, collect data from ultrasonic and GPS sensors, and facilitate data transfer over Bluetooth® Low Energy (LE). Check out our compatible iOS application [here](https://github.com/matthewarmstr/ocean-cleanup-app). 

This project was developed as part of our 2024 UC Davis ECS 193 Senior Design Project in coordination with an EEC 136 design team.

## Firmware Overview
The microcontroller operates the thrust and servo motors using PWMs, allowing them to be operated at specific speeds/positions as desired. The connected ultrasonic reads the distance between itself and an oncoming object by outputting a pulse width, which is then received by the microcontroller with a software counter. Finally, the GPS module sends its latitude and longitude data to the microcontroller every second over a dedicated UART connection.

[describe encoding scheme, Bluetooth...]

## Prerequisites
1. Download and install [PSoC™ Creator](https://www.infineon.com/cms/en/design-support/tools/sdk/psoc-software/psoc-creator/) *(developed using PSoC™ Creator 4.4)*.

## Required Hardware for Sensing, Controls, and Power
1. [PSoC™ 6 BLE Prototyping Kit](https://www.infineon.com/cms/en/product/evaluation-boards/cy8cproto-063-ble/)
2. [RCWL-1601 Ultrasonic Sensor](https://www.amazon.com/JESSINIE-RCWL-1601-Ultrasonic-Ranging-Compatible/dp/B0CB3YCFYY)
3. [GT-U7 GPS Module with Antenna](https://www.amazon.com/dp/B07PRGBLX7)
4. [Underwater Thrust Motor (12-16V)](https://www.amazon.com/APISQUEEN-Underwater-Brushless-Propeller-Propulsion/dp/B0BWJJRQ2Z)
5. [Waterproof 20KG Servo Motor (x2)](https://www.amazon.com/Miuzei-Torque-Digital-Waterproof-Control/dp/B07HNTKSZT)
6. [Buck-Boost Converter (3-16V input, 2.5-9V or 3.3/5V output)](https://www.sparkfun.com/products/15208)
7. [9V Alkaline Battery](https://www.amazon.com/Duracell-MN1604B2Z-Alkaline-General-Purpose/dp/B00PV1EIX8)
8. [11.1V LiPo 1400mAh Battery](https://www.amazon.com/Connector-Airplane-Helicopter-Quadcopter-Multi-Motor/dp/B07L6BNTDV)
9. [Waterproof Box with Cable Holders](https://www.amazon.com/Joinfworld-Outdoor-Extension-Cord-Cover/dp/B0CKZ34N8L)

## Installation
1. Clone this repository.
2. Open PSoC™ Creator and navigate to File > Open > Project/Workspace.
3. Locate the project repository folder on your computer and select `ocean-cleanup-rov-controls.cyprj`.

## Deployment Instructions
Connect your PSoC™ 6 with the included cable. In PSoC™ Creator, click `Program` on the upper-left toolbar and select the `cm0p` core on the device from the toolbar, then connect. The project will be compiled before the microcontroller is flashed (this may take a few minutes).

In the workspace explorer, click on `Pins` under `Design Wide Resources`. Connect the thrust motor (using the ESC), servo motors, and sensors to the appropriate GPIO pins as shown in the displayed pin layout diagram.

***Note: all power entering the microcontroller, along with any logic entering/leaving the GPIO pins, must be 3.3V. Sending 5V to a GPIO pin may result in damage to the PSoC™ 6 microcontroller.***

To give multiple vehicles uniquely identifiable Bluetooth® names, open `TopDesign.cysch`. Double-click on the BLE module, and click on the `GAP Settings` tab. Change the `Device Name` field as desired. Click `Apply` and `OK`, then reprogram the device.
