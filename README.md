## Helping-Hand-for-Partially-Paralyzed-People
This project was a part of our course titled Microprocessors, Microcontrollers, and Embedded Systems Sessional (CSE 316). YouTube link of demonstration: https://youtu.be/mUTkKRFUX7Y

### Overview
The aim of this project is to help partially paralyzed people to remotely control their home appliances and communicate with outside world through a simple electronic interface.
A small electronic interface consisting of two buttons will be attached near the patient's hand. He/she will press the buttons in a certain sequence to execute a certain task.
For example, the command for turning on light is LRL which stands for Left-Right-Left. So, the patient has to press the left button first, then right button, and finally left
button. All the commands in our system are of length 3. So, using just two buttons, the patient can execute eight different tasks. The interface will also consists of GSM module
and heart rate sensor.

Our whole system can be divided into three modules:
1. Room Control
2. Mobile Communication
3. Health Monitoring

#### Room Control
Our room control system is made for two rooms, each consisting of two lights and two fans. The connection between these devices and the patient's interface is wireless. Sonar
sensors will be used to detect which room the patient is currently in. Thus, only one set of commands is enough for controlling similar devices. The fans are attached to servo
motors. The positional data collected from the sonar sensors will also be used to rotate the servo motors i.e. the fans to appropriate angles.

#### Mobile Communication
The patient can also send messages and calls to specific cellphones by giving corresponding commands. The GSM module will be used to execute this mobile communication.

#### Health Monitoring
A finger of the patient will be attached to the heart rate sensor. If the heart rate stays unusual for a certain period of time, an emergency call will be sent to the doctor
automatically through the GSM module.

### Circuit Diagrams
*Transmitter Side*
![Multiple_sensor](https://user-images.githubusercontent.com/45909948/127738167-6f6d1642-f5a5-446f-9013-73025b8399aa.jpg)
*Receiver Side*
![Multiple_sensor - Copy](https://user-images.githubusercontent.com/45909948/127738253-9f960ae7-597d-467b-904c-d29a43c658e1.jpg)
