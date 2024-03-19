#pragma config(Sensor, dgtl4,  ball_collected_limit, sensorDigitalIn)
#pragma config(Motor,  port4,           conveyor_driver, tmotorVex393_MC29, openLoop)

int conveyor_speed = 10;

// Run conveyor motor
// Continue running until limit switch pressed
// After limit switch pressed, reverse conveyor motor for 2 seconds
// Stop motor


// Start this func when ball is detected
// Conveyor can move when robot is moving around
void conveyor_start()
{
	motor(conveyor_driver) = conveyor_speed;
	writeDebugStreamLine("%s", "Conveyor Started/n");
	return;
}

// Conveyor will only reverse if ball has been collected
void conveyor_reverse()
{
	if (SensorValue(ball_collected_limit) == 1)
	{
		motor(conveyor_driver) = -conveyor_speed;
		writeDebugStreamLine("%s", "Conveyor Reversed/n");
	}
	return;
}

// Stops the conveyor after reversing
void conveyor_stop()
{
	motor(conveyor_driver) = 0;
	writeDebugStreamLine("%s", "Conveyor Stopped/n");
	return;
}

task main()
{
	//Starts the conveyor
	conveyor_start();

	// This while loop is when robot is still moving towards the ball, until ball collected
	while (1)
	{
		if (SensorValue(ball_collected_limit) == 1)
		{
			break;
		}
	}

	// When ball has been collected, spit out second ball
	if (SensorValue(ball_collected_limit) == 1)
	{
		conveyor_reverse();
		delay(2000);
	}

	// Stops the conveyor
	conveyor_stop();

}
