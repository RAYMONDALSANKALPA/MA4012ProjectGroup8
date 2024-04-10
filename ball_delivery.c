int delivery_direction = 4; // south, but we are moving north by going backward
int deliver_time_limit = 2000; // work till 10 seconds
int delivery_movement_time = 100; // how much the robot will move before checking
int motor_power_fast = 80;
int motor_power_slow = 40;
int near_delivery_turn_time = 100;

int wait_between_functions_for_debug = 2000;

int bumper_l;
int bumper_r;

void dispense(){
	int motor_power = 100;
	int motor_time = 250;
	dispensor_forward_time(motor_power, motor_time);
	dispensor_stop();
	dispensor_backward_time(motor_power, motor_time);
	dispensor_stop();
}

void move_to_delivery_area(){
	int motor_power = 80;
	int motor_time = delivery_movement_time;
	backward_time(motor_power, motor_time);
}

void turn_to_delivery_area(){
	int motor_power = 80;
	int direction = read_compass();
	while (direction != delivery_direction){
		// TODO: improve this after figuring out the correct direction
		if (direction < delivery_direction)
			turn_right(motor_power);
		else{
			turn_left(motor_power);
		}
		direction = read_compass();
	}
	motor_stop();

	// direction should be correct now
}

int can_dispense_ball(){
	bumper_l = SensorValue(bumper_left);
	bumper_r = SensorValue(bumper_right);

	//if only
	if(bumper_l != 1 && bumper_r != 1){  // both bumpers are pressed
		motor_stop();
		return 1;
	}
	else if (bumper_l != 1 && bumper_r == 1){  // left bumper pressed
		turn_right_time(80, 100);
		// forward_time(80, 100);
		motor_stop();
		return 0;
	}
	else if (bumper_l == 1 && bumper_r != 1){  // right bumper pressed
		turn_left_time(80, 100);
		// forward_time(80, 100);
		motor_stop();
		return 0;
	}
	else{
		return 0;
	}

}

//int is_near_delivery_area(){
//	// check if the robot is near the delivery area using the line sensors
//    int line_BL = SensorValue(IR_BL); // sensor value of 0 means it is on the line
//    int line_BR = SensorValue(IR_BR);

//	if (line_BL == 0 && line_BR == 0){
//		// the robot is near the delivery area
//		// backward(motor_power_slow);
//		motor_stop();
//		return 1;
//	}
//	else if(line_BL == 0 && line_BR != 0){
//		// the robot is nearing the area at an angle, BL is touchnig
//		forward_time(motor_power_slow, near_delivery_turn_time);
//		turn_right_time(motor_power_slow, near_delivery_turn_time);
//		motor_stop();
//		return 0;
//	}
//	else if(line_BL != 0 && line_BR == 0){
//		// the robot is near the delivery area
//		forward_time(motor_power_slow, near_delivery_turn_time);
//		turn_left_time(motor_power_slow, near_delivery_turn_time);
//		motor_stop();
//		return 0;
//	}
//	else{
//		return 0;
//	}
//}

void delivery_retry(){
	// move back a bit
	int motor_power = 80;
	int motor_time = 1000;
	forward_time(motor_power, motor_time);
}

void deliver_ball(){
	int ball_delivered = 0; // ball not delivered yet
	clearTimer(T4);

	while (ball_delivered == 0){

		// turn to delivery area direction
		int direction = read_compass();
		if (direction != delivery_direction){
			turn_to_delivery_area();
		}

		// move_to_delivery_area
		move_to_delivery_area();

		// check proximity to delivery area using the line sensors
		// if (is_near_delivery_area() == 1){

		// 	// dispense();
		// 	// motor_stop();
		// 	// ball_delivered  = 1;
		// 	//check if can dispense
		// 	if (can_dispense_ball()){
		// 		dispense();
		// 		motor_stop();
		// 		ball_delivered  = 1;
		// 	}
		// }

			if (can_dispense_ball()){
				dispense();
				motor_stop();
				ball_delivered  = 1;
			}

		// // Taking too long to deliver, need to retry
		if (time1(T4) > deliver_time_limit){
			delivery_retry();// retry
			clearTimer(T4);
		}
		// //else keep trying!
	}

}
