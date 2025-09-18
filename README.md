# ATmega328P Embedded Drivers
**Temperature monitoring robot with obstacle avoidance and UART communication**

## Description
Microcontroller Module
Autonomous navigation system with remote temperature sensing capabilities for ATmega328P microcontroller.

## Features
- UART serial communication (9600 baud)
- Temperature sensing via ADC
- Ultrasonic obstacle detection and avoidance
- Motor control with PWM
- Real-time autonomous navigation
- Remote command interface

## Hardware Requirements
- ATmega328P microcontroller
- Temperature sensor (analog)
- Ultrasonic sensor (HC-SR04)
- DC motors with driver circuit
- Serial connection for monitoring

## File Structure
```
src/          - Main application code
drivers/      - Hardware driver implementations  
include/      - Header files and function declarations
makefile      - Build configuration
```

## Build Instructions
```bash
make
```

## Usage
**Temperature Reading:**
Send `t` via UART to get temperature reading in Celsius and voltage.

**Autonomous Mode:**
Robot moves forward continuously and avoids obstacles automatically.

## Technical Specifications
- **Language:** C (AVR)
- **Toolchain:** AVR-GCC, avrdude
- **Architecture:** Modular driver system
- **Communication:** 9600 baud UART (8N1)
- **ADC Resolution:** 10-bit
- **Reference Voltage:** 5V

## Driver Modules
- `usart.c/.h` - Serial communication
- `temp.c/.h` - Temperature sensor via ADC
- `ultrasonic.c/.h` - Distance measurement
- `drive.c/.h` - Motor control and movement
- `pwm.c/.h` - Pulse width modulation

## Author
Joseph Oddi Obong - Computer Engineering Student, TU Dublin

## Acknowledgments
Built using course-provided driver templates from TU Dublin Microcontroller Applications module.

## License
MIT License - see LICENSE file for details
