int deliver_time_limit = 15000; // work till 10 seconds

void dispense(){
	writeDebugStreamLine("%s","Dispensing");
	int motor_power = 100;
	int motor_time = 300;
	dispensor_forward_time(motor_power, motor_time);
	dispensor_stop();
	sleep(motor_time);
	dispensor_backward_time(motor_power, motor_time);
	dispensor_stop();
}

void move_to_delivery_area(){
	writeDebugStreamLine("%s","Moving to delivery area");
	int motor_power = 1000;
	backward(motor_power);
}

int can_dispense_ball_ir(){
	writeDebugStreamLine("%s","checking if can dispense ball IR");
	// check if the robot is near the delivery area using the line sensors
	int line_BL = SensorValue(IR_BL); // sensor value of 0 means it is on the line
	int line_BR = SensorValue(IR_BR);
	int direction = read_compass();

	if (direction == 4){
		if (line_BL == 0 && line_BR == 0) return 1;
		else if (line_BL == 0 && line_BR == 1){  // left IR detecting
			turn_right_time(30, 100);
			motor_stop();
			return 1;
		}
		else if (line_BL == 1 && line_BR == 0){  // right IR detecting
			turn_left_time(30, 100);
			motor_stop();
			return 1;
		}
		else return 0;
	}
	else return 0;
}

int can_dispense_ball_bumper(){
	writeDebugStreamLine("%s","can dispense ball bumper");
	int line_BL = SensorValue(IR_BL); // sensor value of 0 means it is on the line
	int line_BR = SensorValue(IR_BR);
	int bumper_l = SensorValue(bumper_left);
	int bumper_r = SensorValue(bumper_right);

	if(bumper_l != 1 && bumper_r != 1){  // both bumpers are pressed
		motor_stop();
		return 1;
	}
	else if (bumper_l != 1 && line_BL == 0){  // left bumper pressed
		turn_right_time(30, 100);
		// forward_time(80, 100);
		motor_stop();
		return 1;
	}
	else if (bumper_l == 1 && line_BR == 0){  // right bumper pressed
		turn_left_time(30, 100);
		// forward_time(80, 100);
		motor_stop();
		return 1;
	}
	else{
		return 0;
	}
}

void delivery_retry(){
	// move back a bit
	int motor_power = 1000;
	int motor_time = 1000;
	forward_time(motor_power, motor_time);
}

void deliver_ball(){
	clearTimer(T3);
	while (1){

		// align to delivery direction
		align_direction();

		clearTimer(T4);
		while(time1(T4) < 750){
			// move_to_delivery_area
			move_to_delivery_area();

			//check if can dispense
			if (can_dispense_ball_ir() || can_dispense_ball_bumper()){

				if (read_compass() == 4){
					//// stop!
					motor_stop();
					// dispense
					dispense();
					// update variables
					ball_found = 0;

					// move back to the collection area
					first_move();
				}
				return;
			}
		}
		clearTimer(T4);

		// Taking too long to deliver, need to retry (needa test irl)
		if (time1(T3) > deliver_time_limit){
			writeDebugStreamLine("%s", "retry delivery");
			delivery_retry();// retry
			clearTimer(T3);
		}
	}
}
