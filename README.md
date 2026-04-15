PROJECT: METHANE GAS DETECTOR (ESP32-DEVKIT-V1)
Source of truth:Hardware Pin mapping

1. SENSOR INPUT (ANALOG)
------------------------------------------
Component: MQ-4 Gas Sensor
ESP32 Pin: GPIO 34 (D34)
Note: Requires Voltage Divider (1k / 2k) to scale 5V -> 3.3V.

2. ALERT SYSTEM (OUTPUTS)
------------------------------------------
Component: Active Buzzer       | Pin: GPIO 25 (D25)
Component: RED Alert LED       | Pin: GPIO 13 (D13)
Component: BLUE Status LED     | Pin: GPIO 12 (D12)
Note: High signal (1) triggers the alert.

3. SPI DISPLAY (OLED/LCD)
------------------------------------------
Protocol: SPI
MOSI (Data): GPIO 23 (D23)
SCK (Clock): GPIO 18 (D18)
CS (Select): GPIO 05 (D5)
Note: Backlight (BL) should be jumped to 3.3V.

4. POWER RAILS
------------------------------------------
VCC (Sensor/Buzzer): 5V (from VIN pin)
VCC (ESP32/LEDs):    3.3V
GND:                 Common Ground for all components.

==========================================================
Ref: Hardware/Kicad schematic.png for circuit logic.
