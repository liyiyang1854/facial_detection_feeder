# facial detection feeder
For the robot arm, we use Dynamixel AX-12A Robot Actuator and ArbotiX-M Robocontroller which is compatible with arduino sketch. There are five steps for the whole process:  <br />
1. wait until the pos error is small <br />
2. grab food <br />
3. move to the position <br />
4. hold for some time <br />
5. move back <br />

For the first step, we receive the data (x,y) from the facial detection program, and add 1 to count if difference between each position is less than 8. And we wait until count equals to 10 which means that the patient is not moving. Then we can let robot arm grab the food and move the food to the patient based on x,y data. The robot arm needs to hold for about five seconds so that the patient has enough to eat the food. Then the robot arm will move back to the intial position and repeat the process.

