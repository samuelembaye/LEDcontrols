LEDcontrol

Overview

LEDcontrol is a system for controlling LEDs using a potentiometer, switches, and resistors. This project utilizes interrupts and timers in C and is designed to run on the Wokwi simulation platform. Development is done using Visual Studio Code, and a Makefile is included to compile the project and generate a .hex file.

Features

LED control using a potentiometer

Switch-based LED toggling

Implementation of interrupts and timers

Uses Wokwi circuit simulation

Compilation via Makefile, generating a .hex file

Configuration using toml

Requirements

Visual Studio Code

Wokwi

GCC (for AVR if targeting microcontrollers)

make

Installation & Usage

Clone the repository:

git clone https://github.com/samuelembaye/LEDcontrols.git
cd LEDcontrols

Open the project in Visual Studio Code.

Build the project using Makefile:

make

The compilation will generate a .hex file that can be uploaded to a microcontroller or tested in Wokwi.



