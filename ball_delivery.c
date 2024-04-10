int delivery_direction = 4; // south, but we are moving north by going backward
int deliver_time_limit = 10000; // work till 10 seconds

int bumper_l;
int bumper_r;

void dispense(){
	int motor_power = 50;
	int motor_time = 800;
	dispensor_forward_time(motor_power, motor_time);
	dispensor_stop();
	dispensor_backward_time(motor_power, motor_time);
	dispensor_stop();
}

void move_to_delivery_area(){
	int motor_power = 80;
	int motor_time = 500;
	backward_time(motor_power, motor_time);
}

void turn_to_delivery_area(){
	int motor_power = 80;
	int left_turn_adjust_time = 100;
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
	turn_left_time(motor_power, left_turn_adjust_time);
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
		motor_stop();
		return 0;
	}
	else if (bumper_l == 1 && bumper_r != 1){  // right bumper pressed
		turn_left_time(80, 100);
		motor_stop();
		return 0;
	}
	else{
		return 0;
	}

}

void delivery_retry(){
	// move back a bit
	int motor_power = 80;
	int motor_time = 1000;
	forward_time(motor_power, motor_time);
}

void deliver_ball(){
	int ball_delivered = 0; // ball not delivered yet
	clearTimer(T4);
	int delivery_time_limit = 7000; // 7 seconds
	while (ball_delivered == 0){
		// turn to delivery area direction
		int direction = read_compass();
		if (direction != delivery_direction){
			turn_to_delivery_area();
		}
		// move_to_delivery_area
		move_to_delivery_area();

		//check if can dispense
		if (can_dispense_ball()){
			dispense();
			ball_delivered = 1;
		}

		// Taking too long to deliver, need to retry
		if (T4 > deliver_time_limit){
			delivery_retry();// retry
			clearTimer(T4);
		}
		//else keep trying!
	}

}