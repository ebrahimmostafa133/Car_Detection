# Car Detection with Mine Detection Functionality

## Description
This project involves creating a system where a car moves forward and intermittently pauses to detect potential mines (represented by black objects). The car operates on the following principles:

1. **Forward Movement:** The car moves forward continuously until it reaches a predefined number of steps (4 steps).
2. **Detection Pause:** Every 0.5 seconds, the car pauses to perform a detection scan for mines.
3. **Mine Detection:** If a black object (mine) is detected during the scan, the car stops, moves backward, and then turns right to avoid the detected obstacle.
4. **No Mine Detected:** If no mines are detected during the scan, the car continues its forward movement until it completes the predefined number of steps. Upon completing the steps, it turns right.

## Functionality
- **Forward Movement:** The car moves forward autonomously.
- **Mine Detection:** Utilizes a detection mechanism to identify black objects as mines.
- **Obstacle Avoidance:** Upon detecting a mine, the car reverses and changes direction to circumvent the obstacle.
- **Step Counting:** Keeps track of the number of steps taken by the car.

## Implementation
- **Hardware:** Utilizes a car chassis with motor drivers, wheels,servo, and IR sensor.
- **Software:** Implemented using a ATmega32 microcontroller. Code logic includes algorithms for movement control, mine detection, and decision-making based on sensor inputs.
