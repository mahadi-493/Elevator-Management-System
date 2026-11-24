# Elevator Management System – Arduino-Based Automation

An Arduino-based elevator management system designed to improve elevator automation, safety, and energy efficiency. The project uses IR sensors, servo motors, and a seven-segment display to manage elevator operations, detect passenger presence, indicate occupancy, and control elevator movement.

Developed as an academic hardware-based project at **United International University (UIU)**.

---

## Features

- **Automatic Door Control:** The elevator door opens based on passenger presence detected by IR sensors.
- **Passenger Detection:** IR sensors detect objects or passengers requesting elevator service.
- **Floor Selection:** Controls elevator movement based on sensor detection and button input.
- **Occupancy Indication:** Displays real-time elevator occupancy and weight information.
- **Full Elevator Indication:** Indicates when the elevator reaches its capacity.
- **Energy Efficiency:** Automatically switches off power when the elevator is idle.
- **Automated Movement:** Uses servo and stepper motors to control elevator mechanisms.

---

## Hardware Components

| Component | Purpose |
|---|---|
| Arduino Mega 2560 | Main microcontroller and control unit |
| IR Sensors | Passenger detection |
| Servo Motors | Elevator door and movement control |
| Stepper Motor | Controlled mechanical movement |
| Seven-Segment Display | Numerical floor/status indication |
| LED Lights | Visual status indication |
| Push Button Switch | User input and floor selection |
| Resistors | Circuit current regulation |
| Jumper Wires | Hardware connections |
| Breadboard | Circuit prototyping |

---

## Working Mechanism

1. IR sensors detect the presence of a passenger or object at a floor.
2. The elevator responds to the sensor input and button selection.
3. The elevator moves to the requested floor.
4. The door opens when passenger presence is detected.
5. Servo and stepper motors control the elevator's mechanical movement.
6. The display and indicators provide elevator status and occupancy information.
7. The system switches off power when no passenger is present and the elevator is idle.

---

## System Architecture

The Arduino Mega 2560 acts as the central processing unit, receiving input from IR sensors and push buttons. Based on the received signals, it controls the motors, indicators, and display.

**System Flow:**

```text
IR Sensors / Push Buttons
          |
          v
    Arduino Mega 2560
          |
    +-----+------+
    |     |      |
    v     v      v
  Motors LEDs  Display
    |
    v
Elevator Movement
and Door Control
```

---

## Hardware Setup

The project was implemented as a physical elevator prototype using a constructed elevator structure, Arduino Mega, sensors, motors, and electronic components.

---

## Technologies & Tools

- **Programming:** C/C++ (Arduino)
- **Microcontroller:** Arduino Mega 2560
- **Sensors:** IR Sensors
- **Actuators:** Servo Motor, Stepper Motor
- **Display:** Seven-Segment Display
- **Electronics:** LEDs, Resistors, Push Buttons, Breadboard

---

## Project Team

Department of Computer Science and Engineering  
United International University (UIU), Dhaka, Bangladesh

| Team Member | Student ID |
|---|---|
| Abdullah Al Masud Bhuiyan | 011221074 |
| Mahadi Hasan | 0112230493 |
| Kaium Al Limon | 011221291 |
| Masud Sarrowar | 011213099 |
| Tanvur Ahamad Jibon | 011202328 |

---

## Project Documentation

The project report contains:

- Introduction and project overview
- Hardware component descriptions
- Component cost calculation
- Prototype photographs
- System implementation details

---

## License

This project was developed for academic and educational purposes at United International University.