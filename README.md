# Methane Gas Detector System

##  Project Overview
An IoT-based methane gas detection system using an **ESP32** and an **MQ-4 sensor**. The system monitors gas levels in real-time, providing visual feedback on an SPI display and audible alerts via a buzzer when thresholds are exceeded.

##  Group Collaboration
Braton Mulwa
Gicuna Kuriah
Enos Odero

##  Hardware Components
Microcontroller: ESP32 DevKit V1
Sensor: MQ-4 Methane Gas Sensor
Alerts: Red/Blue LEDs & Active Buzzer
Display: 8-pin SPI OLED/LCD
Safety: Voltage Divider ($1k\Omega$ and $2k\Omega$ resistors)

##  Project Structure
* `/Hardware`: Contains KiCad schematic files and wiring diagrams.
* `/Firmware`: (Coming Soon) Arduino/C++ source code.
* `pin_mapping.txt`: Logical pin definitions for breadboard assembly.

##  How to Build
1. Refer to `Hardware/Kicad schematic.png` for wiring.
2. Ensure the voltage divider is placed between the MQ-4 Analog Out and ESP32 GPIO 34.
3. Open the source code file in Arduino IDE and upload to the ESP32.
