![Arduino](https://img.shields.io/badge/Arduino-Pro_Micro-00979D?logo=arduino&logoColor=white)
![Platform](https://img.shields.io/badge/OS-Windows_%7C_macOS_%7C_Linux-blue)
![License](https://img.shields.io/badge/License-MIT-green)


# simple Media Knob

A USB HID media control knob built with an Arduino Pro Micro (ATmega32U4) and a KY-040 rotary encoder. It acts as a plug-and-play USB media device for controlling system volume, playback, track navigation, and system mute across Windows, macOS, and Linux (including Bazzite / SteamOS).

---

## 🛠️ Hardware Requirements

* **Microcontroller:** Arduino Pro Micro (ATmega32U4, 5V/16MHz)
* **Input Device:** KY-040 Rotary Encoder Module
* **Connection:** USB-C / Micro-USB Data Cable (depending onyour board)

---

## 🔌 Wiring Diagram

Connect the KY-040 encoder pins to the Arduino Pro Micro as follows:

| KY-040 Pin | Arduino Pro Micro Pin | Description |
| :--- | :--- | :--- |
| **CLK** | Pin 2 | Encoder Clock Signal |
| **DT** | Pin 3 | Encoder Data Signal |
| **SW** | Pin 4 | Push Button Signal |
| **+ (VCC)** | VCC (5V) | Power |
| **GND** | GND | Ground |

---

## 🎛️ Controls & Features

* **Rotate Clockwise:** System Volume Up
* **Rotate Counter-Clockwise:** System Volume Down
* **Single Press:** Play / Pause
* **Double Press:** Next Track
* **Triple Press:** Previous Track
* **Press & Hold:** System Mute/Unmute

---

## 💻 Software & Installation

1. Install the **Arduino IDE**.
2. Go to **Tools > Manage Libraries...**, search for **HID-Project** (by NicoHood), and install it.
3. Select board: **Tools > Board > Arduino Micro** (or *SparkFun Pro Micro 5V/16MHz*).
4. Select your COM port under **Tools > Port**.
5. Flash `simple-media-knob.ino` to your board.

---

## 🐧 Linux / Bazzite Compatibility Note

This project uses both `BootKeyboard` and `Consumer` HID initializations to ensure Linux distributions (including SteamOS/Bazzite) properly attach input event handlers (`/dev/input/event*`) upon boot.

---

## 🧰 3D Printed Enclosure

There are no enclosures yet because I didn't have the time to design one yet.
.stl files will be added further down the line.
