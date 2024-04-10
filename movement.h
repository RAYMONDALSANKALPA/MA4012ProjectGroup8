// ! This program is for the functions needed for movement
// Assume that the declarations are all done in the robot_main.c


// Functions to move the motors
void forward(int motor_power){
    motor[left_driver] = motor_power;
    motor[right_driver] = motor_power;
}

void backward(int motor_power){
    motor[left_driver] = -motor_power;
    motor[right_driver] = -motor_power;
}

void turn_left(int motor_power){
    motor[left_driver] = -motor_power;
    motor[right_driver] = motor_power;
}

void turn_right(int motor_power){
    motor[left_driver] = motor_power;
    motor[right_driver] = -motor_power;
}

void motor_stop(){
    motor[left_driver] = 0;
    motor[right_driver] = 0;
}

void conveyor_start(int motor_power){
    motor[conveyor_driver] = motor_power;
}

void conveyor_stop(){
	motor(conveyor_driver) = 0;
}

void conveyor_reverse(int motor_power){
    motor[conveyor_driver] = -motor_power;
}

void dispensor_forward(int motor_power){
    motor[dispenser_driver] = motor_power;
}

void dispensor_backward(int motor_power){
    motor[dispenser_driver] = -motor_power;
}

void dispensor_stop(){
    motor[dispenser_driver] = 0;
}

void forward_time (int motor_power, int motor_time){
    forward(motor_power);
    wait1Msec(motor_time);
}

void backward_time (int motor_power, int motor_time){
    backward(motor_power);
    wait1Msec(motor_time);
}

void turn_left_time (int motor_power, int motor_time){
    turn_left(motor_power);
    wait1Msec(motor_time);
}

void turn_right_time (int motor_power, int motor_time){
    turn_right(motor_power);
    wait1Msec(motor_time);
}

//void conveyor_forward_time(int motor_power, int motor_time){
//    conveyor_start(motor_power);
//    wait1Msec(motor_time);
//}

//void conveyor_backward_time(int motor_power, int motor_time){
//    conveyor_reverse(motor_power);
//    wait1Msec(motor_time);
//}

void dispensor_forward_time(int motor_power, int motor_time){
    dispensor_forward(motor_power);
    wait1Msec(motor_time);
}

void dispensor_backward_time(int motor_power, int motor_time){
    dispensor_backward(motor_power);
    wait1Msec(motor_time);
}
