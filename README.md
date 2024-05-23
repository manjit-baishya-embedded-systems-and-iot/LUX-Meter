# Lux Meter with LDR

## Overview

Lux Meter with LDR is an IoT project designed to measure the intensity of light using a Light Dependent Resistor (LDR) and an Arduino UNO. The collected data is then sent to an ESP32 microcontroller, which processes the information and hosts a web server to display the readings in real-time through a user-friendly web interface.

## Table of Contents
- [**Project Structure**](#project-structure)
- [**Features**](#features)
- [**Hardware Requirements**](#hardware-requirements)
- [**Software Requirements**](#software-requirements)
- [**Installation**](#installation)
- [**Working**](#working)
- [**Usage**](#usage)
- [**Contributing**](#contributing)
- [**License**](#license)
- [**Acknowledgments**](#acknowledgments)

## Features
- Measures light intensity and converts it to lux.
- Displays real-time lux values on a web interface.
- Uses Arduino UNO and ESP32 for data processing and transmission.
- Provides a simple HTTP server to fetch data via GET requests.
- User-friendly web interface with automatic updates.

## Hardware Requirements
- Arduino UNO
- ESP32
- LDR Sensor
- Connecting wires
- Breadboard (optional)

## Software Requirements
- Arduino IDE
- Micropython for ESP32
- VS Code 
- Jupyter Notebook
- Python
- Browser

## Installation

### Arduino Setup
1. **Connect the LDR to Arduino UNO**:
    - Connect one end of the LDR to the `A0` pin.
    - Connect the other end to `5V` through a resistor (10kΩ).
    - Connect the junction of LDR and resistor to `GND`.

2. **Upload the Arduino Code**:
    - Upload the `LuxMeter.ino` code provided in the Arduino folder.

### ESP32 Setup
1. **Connect ESP32 to WiFi**:
    - Modify the `boot.py` script to include your WiFi credentials.
    - If needed, set a static IP address in the `boot.py` script.
    - Upload the `boot.py` and `main.py` files provided in the ESP32 folder.

2. **Set Up the Web Server**:
    - Upload the `index.html`, `script.js`, and `styles.css` files provided in the Web folder to a web server.

## Working
The LDR is setup alog with a 10kΩ resistor in a voltage divider circuit. The corresponding voltages are marked with relevant LUX Values with a `SAMSUNG J7 Pro Light Sensor`. The Experiment is carriedon a few timesand the values are tabulated and furthur put into experiment as elaborated in `equation.ipynb`. These values are then put into `UNO` and the correspondingLUX values against the LDR Voltages are calulated.

These two values are sent over to the ESP32 via UART. The ESP32 then starts a local server at `192.168.1.45` where these two values are packed into a `JSON` and sent over `WiFi`. These two values are then retrieved by a corresponding webpage and displayed with customized CSS. 

## Usage
1. **Power Up**: Connect both Arduino UNO and ESP32 to power sources.
2. **Access Web Interface**: Open a web browser and navigate to the IP address of the ESP32 web server.
3. **Monitor Light Intensity**: The web page will display real-time LDR voltage and lux values.

## Contributing
Contributions are welcome! Please fork this repository and submit pull requests for any enhancements or bug fixes. Make sure to follow the coding standards and include appropriate documentation for any changes.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments
Special thanks to all the open-source projects and libraries that made this project possible.