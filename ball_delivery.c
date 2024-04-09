int bumper_l;
int bumper_r;

void dispenser_test(){
	int motor_power = 50;
	int motor_time = 800;
	dispensor_forward_time(motor_power, motor_time);
	dispensor_stop();
	dispensor_backward_time(motor_power, motor_time);
	dispensor_stop();
}

void dispense(){
	backward(60);
	while(1){
		bumper_l = SensorValue(bumper_left);
		bumper_r = SensorValue(bumper_right);

		if(bumper_l != 1 && bumper_r != 1){
			motor_stop();
			dispenser_test();
		}
	}
}
