#pragma config(Sensor, in2,    sharp_front_top, sensorAnalog)
#pragma config(Sensor, in3,    sharp_back_top, sensorAnalog)
#pragma config(Sensor, in7,    sharp_bl,       sensorAnalog)
#pragma config(Sensor, in8,    sharp_bs,       sensorAnalog)
#pragma config(Sensor, dgtl12, ball_limit,     sensorDigitalIn)
#pragma config(Sensor, dgtl4, front_l_line, sensorDigitalIn)
#pragma config(Sensor, dgtl3, front_r_line, sensorDigitalIn)
#pragma config(Sensor, dgtl2, back_l_line, sensorDigitalIn)
#pragma config(Sensor, dgtl1, back_r_line, sensorDigitalIn)
#pragma config(Motor,  port4,           right_driver,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port2,           trapdoor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           conveyor_driver, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           left_driver,   tmotorVex393_MC29, openLoop, reversed)

#include "sensor.h"

void spinning_search()
{
	writeDebugStreamLine("%s", "spinning searching");
	float rot_time = 6000;
	float rot_spd = 60;

	// using timer T1
	clearTimer(T1);

	// Rotate CW
	motor(left_driver) = -rot_spd;
	motor(right_driver) = rot_spd;
	while (1)
	{
		// Scan for ball
		scan_ball();
		if (ball_found == 1)
		{
			motor(left_driver) = 0;
			motor(right_driver) = 0;
			//sleep(1000);
			scan_ball();
			if (ball_found == 0)
			{
				spinning_search();
			}
			writeDebugStreamLine("%s", "ball found... from spin search");
			return;
		}
		else
		{
			if (time1(T1) > rot_time)
			{
				motor(left_driver) = 0;
				motor(right_driver) = 0;
				writeDebugStreamLine("%s", "motor stopped");
				ball_found = 0;
				return;
			}
		}
	}
}

void move_forward()
{
	writeDebugStreamLine("%s", "moving forward");
	float motor_spd = 60;
	clearTimer(T3);
	// move forward
	motor(left_driver) = motor_spd;
	motor(right_driver) = motor_spd;
	while (time1(T3) < 4000)
	{
		// scan ball
		scan_ball();
		if (ball_found == 1)
		{
			motor(left_driver) = 0;
			motor(right_driver) = 0;
			writeDebugStreamLine("%s", "ball found in moving forward");
			return;
		}
	}
	motor(left_driver) = 0;
	motor(right_driver) = 0;
	ball_found = 0;
	return;
}

task main()
{
	startTask(sensor_calibration);
	while(1){
		if(ball_found == 1)
		{
			writeDebugStreamLine("%s", "congratz, should be initialising ball collection mechanism");
		}
		else if (ball_found == 0)
		{
			spinning_search();
			if(ball_found == 0)
			{
				move_forward();
			}
		}
	}
}
