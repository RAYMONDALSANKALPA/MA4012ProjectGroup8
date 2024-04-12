# MA4012ProjectGroup8
This repository is for the MA4012 tennis ball collecting competition.

# Diagonistic steps
Whenever any changes are done, follow this order to test if everything in the robot is working.
1. Power entering the robot: check if the power connection is stable
2. Sensor calibaration: connect the robot to the laptop and switch it on. Then, check the sensors under calibration.
2.1. IR sensors (use the black cardboard with yellow tape on it)
2.2. distance sensors (analog)
2.3. Ball limit switch, (and other limit switches if used)
3. Movement test in the main function, check the motors

# Planning for testing
Order in which I will test the robot and fix everything:
1. Ball delivery system
2. Ball search
3. Boundary detection
4. Enemy detection
5. Integrated tests 1 + 2
6. Integrated tests 1 + 2 + 3
7. Integrated tests 1 + 2 + 3 + 4

# To do
1. Move forward during ball collection proportional to the distance it is from the ball.
2. Logic flow is not smooth. There is an extra "mini sweep" suddenly. Only do it if you cannot find the ball.

distance  121.874252 ball found:  0
turn left
distance  121.874252 ball found:  0
turn left
distance  121.874252 ball found:  0
turn left
distance  121.874252 ball found:  0
turn left
distance  121.874252 ball found:  0
turn left
distance  70.667252 ball found:  0
ball found
mini sweep
ball found

3. Robot not able to turn to correct direction. when pushed too much to the side. need to fix.


# Changes made
1. added condition in the if statement of the main code such that it searches only when (ball_found == 1 && ball_collected_limit == 1), meaning the the ball is found and the ball limit switch does not detect a ball (robot did not collect ball)
