// ! This program is for the functions needed for movement
// Assume that the declarations are all done in the robot_main.c


// Functions to move the motors
void forward(int motor_power){
    motor[leftmotor] = motor_power;
    motor[rightmotor] = motor_power;
}

void backward(int motor_power){
    motor[leftmotor] = -motor_power;
    motor[rightmotor] = -motor_power;
}

void turn_left(int motor_power){
    motor[leftmotor] = -motor_power;
    motor[rightmotor] = motor_power;
}

void turn_right(int motor_power){
    motor[leftmotor] = motor_power;
    motor[rightmotor] = -motor_power;
}

void rest_motor(){
    motor[leftmotor] = 0;
    motor[rightmotor] = 0;
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

void conveyor_forward(int motor_power){
    motor[conveyor] = motor_power;
}

void conveyor_backward(int motor_power){
    motor[conveyor] = -motor_power;
}

void dispensor_forward(int motor_power){
    motor[dispensor] = motor_power;
}

void dispensor_backward(int motor_power){
    motor[dispensor] = -motor_power;
}

void rest_conveyor(){
    motor[conveyor] = 0;
}

void rest_dispensor(){
    motor[dispensor] = 0;
}

void conveyor_forward_time(int motor_power, int motor_time){
    conveyor_forward(motor_power);
    wait1Msec(motor_time);
}

void conveyor_backward_time(int motor_power, int motor_time){
    conveyor_backward(motor_power);
    wait1Msec(motor_time);
}

void dispensor_forward_time(int motor_power, int motor_time){
    dispensor_forward(motor_power);
    wait1Msec(motor_time);
}

void dispensor_backward_time(int motor_power, int motor_time){
    dispensor_backward(motor_power);
    wait1Msec(motor_time);
}

// Testing routines
void left_motor_test(){
    motor[leftmotor] = 0;
    wait1Msec(2000);
    motor[leftmotor] = 100;
    wait1Msec(2000);
    motor[leftmotor] = 0;
}

void right_motor_test(){
    motor[rightmotor] = 0;
    wait1Msec(2000);
    motor[rightmotor] = 100;
    wait1Msec(2000);
    motor[rightmotor] = 0;
}

void movement_test(){
    int motor_power = 50;
    int motor_time = 1000;
    int rest_time = 2000;
    rest_motor();
    forward_time(motor_power, motor_time);
    rest_motor();
    backward_time(motor_power, motor_time);
    rest_motor();
    turn_left_time(motor_power, motor_time);
    rest_motor();
    turn_right_time(motor_power, motor_time);
    rest_motor();
}

void conveyor_test(){
    int motor_power = 50;
    int motor_time = 3000;
    int rest_time = 2000;
    rest_conveyor();
    conveyor_forward_time(motor_power, motor_time);
    rest_conveyor();
    conveyor_backward_time(motor_power, motor_time);
    rest_conveyor();
}

void dispensor_test(){
    int motor_power = 50;
    int motor_time = 800;
    int rest_time = 2000;
    rest_dispensor();
    dispensor_forward_time(motor_power, motor_time);
    rest_dispensor();
    dispensor_backward_time(motor_power, motor_time);
    rest_dispensor();
}

void search_movement_simple(){
    int motor_power = 50;
    int motor_time = 500;
    forward_time(motor_power, motor_time);
    rest_motor();
}

void closing_movement_simple(){
    int motor_power = 50;
    int motor_time = 200;
    forward_time(motor_power, motor_time);
    rest_motor();
}

void ball_collection(){
    int motor_power = 50;
    int motor_time = 500;
    int conveyor_power = 63; 
    int conveyor_time = 3000;
    forward(motor_power);
    conveyor_forward(conveyor_power);
    wait1Msec(motor_time);
    rest_motor();
    wait1Msec(conveyor_time);
    rest_conveyor();
}