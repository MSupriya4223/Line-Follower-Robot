# Smart Line Follower Robot

This repository contains the Arduino source code and documentation for a Smart Line Follower Robot. The robot autonomously follows a black line on a white surface and incorporates an obstacle detection system to halt movement when an object is detected in its path.

## Features
* **Line Tracking:** Utilizes three IR sensors (Left, Center, Right) to continuously monitor the path.
* **Obstacle Avoidance:** Employs an HC-SR04 ultrasonic sensor to measure distance via echolocation, automatically stopping the motors if an obstacle is detected within 18 cm.
* **Smart Recovery Logic:** If the line is lost, the algorithm recalls the last known direction and executes a search routine to reacquire the path.
* **Offset Calibration:** Configurable motor offset variables are included in the source code to balance uneven DC motor speeds.

## Hardware Components
* Arduino Uno Rev3
* 3x IR Sensor Modules
* 1x Ultrasonic Sensor (HC-SR04)
* 1x Motor Driver Module
* 2x DC Motors with Wheels
* Robot Chassis
* **Power System:** 2S Lithium Battery configuration yielding 7.4V, protected by a Battery Management System (BMS), and regulated by a Buck Converter stepping down the voltage to 5V for the Arduino.

## Pin Configuration

### Sensors
* **Left IR Sensor:** D2
* **Center IR Sensor:** D4
* **Right IR Sensor:** D3
* **Ultrasonic Trig:** D12
* **Ultrasonic Echo:** D11

### Motor Driver
* **ENA (Right Motor Speed):** D5
* **IN1 (Right Motor Forward):** D6
* **IN2 (Right Motor Backward):** D7
* **IN3 (Left Motor Backward):** D8
* **IN4 (Left Motor Forward):** D9
* **ENB (Left Motor Speed):** D10

## Installation & Upload
1. Clone this repository to your local machine.
2. Open the `.ino` file using the Arduino IDE.
3. Connect the Arduino Uno to your computer via USB.
4. Select the correct COM port and "Arduino Uno" under the Tools > Board menu.
5. Compile and upload the code.

## Usage & Calibration
1. Draw a path using black electrical tape on a white surface.
2. Prior to connecting power to the Arduino, use a multimeter to verify the buck converter output is tuned exactly to 5V. 
3. Place the robot on the path, ensuring the middle IR sensor is positioned directly over the black line.
4. Turn on the power supply for both the Arduino and the motor driver.
5. **Troubleshooting:** If the robot moves backward instead of forward, reverse the motor wiring connected to the motor driver. If the robot does not track straight on a straight line, modify the `LEFT_MOTOR_OFFSET` and `RIGHT_MOTOR_OFFSET` constants in the `.ino` file to equalize the speed.

## Contact & Support
* **Author:** Supriya Mandal
* **Organization:** Ceemsys Technologies
* **Website:** https://ceemsys.com
* **Email:** info@ceensystechnologies.com
* **GitHub:** https://github.com/MSupriya4223
