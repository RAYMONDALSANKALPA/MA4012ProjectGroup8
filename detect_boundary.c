void stop_motor()
{
    motor(left_driver) = 0;
    motor(right_driver) = 0;
    return;
}

void control_motor(int left_speed, int right_speed)
{
    motor(left_driver) = left_speed;
    motor(right_driver) = right_speed;
    return;
}

int scan_boundary()
{
    int frontLeft = 0;
    int frontRight = 0;
    int backLeft = 0;
    int backRight = 0;

    if (SensorValue(IR_FL) == 0)
    {
        frontLeft = 1;
    }
    if (SensorValue(IR_FR) == 0)
    {
        frontRight = 10;
    }
    if (SensorValue(IR_BL) == 0)
    {
    	backLeft = 100;
    }
    if (SensorValue(IR_BR) == 0)
    {
    	backRight = 1000;
    }

    return frontLeft+frontRight+backLeft+backRight;
}

void avoid_boundaries(int sensor_number)
{
	if (SensorValue(ball_limit) == 0 && read_compass() == 4){
		return;
	}

	int array_element = 4;

	switch(sensor_number)	{
		case 1:
			array_element = 0;
			break;
		case 10:
			array_element = 1;
			break;
		case 100:
			array_element = 2;
			break;
		case 1000:
			array_element = 3;
			break;
		case 11:
			array_element = 0;
			break;
	}

	if (array_element != 4) {
		if (SensorValue(ball_limit) == 0) {
			array_element = 4 + array_element;
		}

		hogCPU();
		writeDebugStreamLine("%s %d", "boundary detected!", array_element);
		//writeDebugStreamLine("%d", array_element);

		//FL,FR,BL,BR,2BR,2BL,2FR,2FL
		int move[] = {-80, -80, 80, 80, -80, -80, 80, 80};
		int rotate_left[] = {100, -100, 30, -30, -30, 30, -100, 100};
		int rotate_right[] = {-100, 100, -30, 30, 30, -30, 100, -100};

	  clearTimer(T2);
	  while (time1(T2) < 200)	{
	  	stop_motor();
	  }
	  clearTimer(T2);
	  while (time1(T2) < 1200)	{
	  	control_motor(move[array_element], move[array_element]);
	  }
	  clearTimer(T2);
	  while (time1(T2) < (400 + random(200)))	{
	  	control_motor(rotate_left[array_element], rotate_right[array_element]);
	  }
	  stop_motor();
	  releaseCPU();
	}
}

task detect_boundary()
{
	while (true){
		int boundary_value = scan_boundary();
		avoid_boundaries(boundary_value);
	}
}
