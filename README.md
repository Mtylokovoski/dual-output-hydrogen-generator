

 Hydrogen Based Energy Storage System

 Overview

The **Hydrogen Based Energy Storage System** is an embedded control system designed to monitor, manage, and regulate hydrogen production and consumption in a small-scale hydrogen energy setup. The system uses an **Arduino Mega 2560** to measure electrical parameters, calculate hydrogen generation through electrolysis, estimate hydrogen consumption from the load, and automatically control the electrolysis process based on storage levels.

This project demonstrates the integration of **electronics, sensors, embedded programming, and energy system modeling**, making it suitable for educational demonstrations and small research prototypes in renewable energy systems.

---
 Features

* Real-time monitoring of **electrolyzer current and voltage**
* Measurement of **load current and voltage**
* Calculation of **hydrogen production using Faraday’s law**
* Estimation of **hydrogen consumption based on load power**
* Automatic **hydrogen storage level tracking**
* **Relay control of electrolysis process**
* **EEPROM storage** for persistent hydrogen storage values
* Serial monitoring for debugging and data logging
* Modular firmware architecture for easy expansion



System Architecture

The firmware is organized into modular components:

```
Hydrogen Energy System
│
├── Main Control Loop
│
├── Sensor Interface
│   ├── Current sensors (ACS712)
│   └── Voltage sensors (Voltage divider)
│
├── Hydrogen Logic
│   ├── Production calculation
│   ├── Consumption estimation
│   └── Storage update
│
├── Control System
│   └── Electrolysis relay switching
│
└── Display / Monitoring
```

---

Hardware Requirements

* Arduino Mega 2560
* ACS712 Current Sensors
* Voltage Divider Circuits
* Relay Module
* Electrolyzer Unit
* Hydrogen Storage Tank (experimental)
* Power Supply
* Optional: OLED or LCD display



 Software Structure

The firmware consists of several files:


hydrogen_based_energy_storage.ino   -> Main program
config.h                            -> System constants and pin configuration
sensors.h / sensors.cpp             -> Sensor reading functions
logic.h / logic.cpp                 -> Hydrogen production and consumption logic
display.h / display.cpp             -> System display functions



Hydrogen Production Model

Hydrogen generation is calculated using Faraday’s Law of Electrolysis.

Formula used:


H₂ Production = (η × I × t) / (n × F)


Where:

| Variable | Description                               |
| -------- | ----------------------------------------- |
| η        | System efficiency                         |
| I        | Electrolyzer current                      |
| t        | Time                                      |
| n        | Number of electrons per hydrogen molecule |
| F        | Faraday constant                          |

The resulting hydrogen amount is converted into liters using molar volume

---

 Hydrogen Consumption Model

Hydrogen consumption is estimated using the energy demand of the connected load.

```
Energy = Power × Time
```

Hydrogen consumption is calculated using the Higher Heating Value (HHV) of hydrogen and the fuel cell efficiency.

---

Storage Control Logic

The system automatically controls electrolysis using storage thresholds.

| Storage Level | System Action    |
| ------------- | ---------------- |
| ≤ 50%         | Electrolysis ON  |
| ≥ 90%         | Electrolysis OFF |

This prevents:
Overfilling of hydrogen storage
Unnecessary electrolysis operation



EEPROM Data Storage

The hydrogen storage value is stored in EEPROM memory so that the system can restore the last known storage level after power loss.

This prevents incorrect calculations after system restarts.


 Serial Output Example

Example monitoring output from the serial console:


120 | 1.80A | 2.10V | 0.50A | 5.00V | 3.25L | ON


Meaning:


Time | Electrolyzer Current | Electrolyzer Voltage | Load Current | Load Voltage | Hydrogen Storage | Electrolysis State



Safety Considerations

Hydrogen is a highly flammable gas. When working with hydrogen systems:

* Ensure proper ventilation
* Avoid sparks or open flames
* Use pressure-rated containers
* Implement leak detection
* Use safety valves when possible





Future Improvements

Possible upgrades include:

* OLED graphical display
* Hydrogen pressure sensor integration
* Hydrogen leak detection system
* IoT monitoring using WiFi
* Data logging to SD card
* Advanced energy efficiency analytics



 Author

Ephraim Baraka
Mechatronic Engineering Technician Level 6
Taita Taveta National Polytechnic

Final Year Project:
 Dual Output Hydrogen Energy Kit


