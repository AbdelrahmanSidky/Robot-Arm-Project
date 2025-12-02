# Robot-Arm-Project
This repository contains the code and documentation for Robot Arm Project. The arm is designed for educational purposes, it is the final project for EEL-4664 Kinematics and Control of Robot Systems. It utilizes Arduino using AVR C for control and movement.


# Introduction 
      
  For this project we used a 3D printed robot arm with 5 degrees of freedom designed by Dejan. The robot consisted of several links each rotating on a revolute joint and the end effector was a claw. The goal for this project was to use this arm to pick up a rubber duck from a set point then drop it in a container. The duck’s position was known. In order to compare our code to others’, we participated in a competition. The competition tested how many ducks each group could grab and drop in a minute, manually replacing the duck for each cycle.


# Materials
5v, 2A, Power supply, 3 SG90 9g Micro Servos, 3 MG996R 55g Servos 

# Methods
  In the beginning we were using Arduino IDE with the servo.h library to control the servos, but we had a lot of problems from stability to angles, so we developed our own code from scratch in AVR C We did not use any servo library we developed our own code to control the servos using the internal AVR Timer one. We used CTC mode with timer one to generate PWM with 20ms period to control the servos. In the code we control the time of the high pulse which represents an angel. 
  In another word a servo receives a PWM with a period of 20ms most of which is low, while the time that signal is high from 600micro seconds to 2400micro seconds presents from zero degree angle to 180+ degree angle. 
  Using this logic we control that value between  600micro seconds to 2400micro for every servo to set its position. Then we created the pattern of movements, a set of values to go through with delays in between to pick up the duck and place the duck and repeat
