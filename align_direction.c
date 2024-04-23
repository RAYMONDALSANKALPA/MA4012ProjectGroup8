int delivery_direction = 4;
int direction = read_compass();

void turning_direction(int motor_power, int direction)
{
	if (direction < delivery_direction){
		turn_right(motor_power);
	}
	else{
		turn_left(motor_power);
	}
}

void turn_to_south()
{
	motor_stop();
	wait1Msec(100);
	writeDebugStreamLine("%s","Turning to face south");
	while (read_compass() != delivery_direction){
		direction = read_compass();
		if (direction == 3 || direction == 5){
			turning_direction(35, direction);
		}
		else {
			turning_direction(70, direction);
		}
	}
}

void align_direction()
{
	direction = read_compass();
	if (direction != delivery_direction){
		writeDebugStreamLine("%d", direction);
		turn_to_south();
	}
}
