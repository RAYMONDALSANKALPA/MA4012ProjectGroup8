#pragma config(Sensor, in2,    sharp_front_top, sensorAnalog)
#pragma config(Sensor, in3,    sharp_back_top, sensorAnalog)
#pragma config(Sensor, in7,    sharp_bl,       sensorAnalog)
#pragma config(Sensor, in8,    sharp_bs,       sensorAnalog)
#pragma config(Sensor, dgtl11, ball_limit,     sensorDigitalIn)
#pragma config(Motor,  port2,           right_driver,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           trapdoor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           conveyor_driver, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           left_driver,   tmotorVex393_MC29, openLoop, reversed)

#include "sensor.h"

task main()
{
	startTask(sensor_calibration);
	while(1)
	{

		motor(left_driver) = -80;
		motor(right_driver) = 80;
	}

}
