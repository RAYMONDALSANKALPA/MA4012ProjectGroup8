#pragma config(Sensor, in2,    sharp_front_top, sensorAnalog)
#pragma config(Sensor, in3,    sharp_back_top, sensorAnalog)
#pragma config(Sensor, in7,    sharp_bl,       sensorAnalog)
#pragma config(Sensor, in8,    sharp_bs,       sensorAnalog)
#pragma config(Sensor, dgtl1,  IR_BR,    sensorDigitalIn)
#pragma config(Sensor, dgtl2,  IR_BL,    sensorDigitalIn)
#pragma config(Sensor, dgtl3,  IR_FR,   sensorDigitalIn)
#pragma config(Sensor, dgtl4,  IR_FL,   sensorDigitalIn)
#pragma config(Sensor, dgtl5,  compass1,       sensorDigitalIn) //
#pragma config(Sensor, dgtl6,  compass2,       sensorDigitalIn)
#pragma config(Sensor, dgtl7,  compass3,       sensorDigitalIn)
#pragma config(Sensor, dgtl8,  compass4,       sensorDigitalIn) // yellow of the compass goes here
#pragma config(Sensor, dgtl10, bumper_left,    sensorDigitalIn)
#pragma config(Sensor, dgtl11, bumper_right,   sensorDigitalIn)
#pragma config(Sensor, dgtl12, ball_limit,     sensorDigitalIn)
#pragma config(Motor,  port2,           dispenser_driver, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           conveyor_driver, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           right_driver,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           left_driver,   tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "sensor.h"
#include "movement.h"
#include "startup.c"
#include "searching_algorithm.c"
#include "ball_collection.c"
#include "ball_delivery.c"
#include "detect_boundary.c"
#include "detect_opponent.c"


task main()
{
	// threaded task that checks for sensor at all time
	startTask(sensor_calibration);
	startTask(detect_boundary);
	//startTask(detect_opponent);
	// inital movement where we move half the field b4 executing spin search
	//first_move();
	while(1)
	{
	//	if (ball_found == 1)
	//	{
	//		// ball collecion mechanism activate here
	//		writeDebugStreamLine("%s", "begin collection mechanism");
	//		//sleep(2000);
	//		go_to_ball();
	//		if (ball_collected_limit != 1){
	//			// insert delivery mechanism

	//			stopTask(detect_boundary);
	//			deliver_ball();
	//			//writeDebugStreamLine("%d", ball_delivered);
	//			if (ball_delivered == 1){
	//				//writeDebugStreamLine("%s", "ball delivered");
	//				startTask(detect_boundary);
	//				first_move();
	//			}
	//		}
	//		else if (ball_collected_limit ==1)ball_found = 0; // sends it back into ball_found searching loop
	//	}
	//	else if (ball_found == 0)
	//	{
	//		sweeping_search();
	//		if (ball_found == 0)
	//		{
	//			writeDebugStreamLine("%s", "ball not found, move forward and repeat search");
				//move_forward();
		turn_left(1000);
			//}
	//		writeDebugStreamLine("%d", ball_collected_limit);
	//		if (SensorValue(ball_limit) == 0) ball_found = 1;
	//	}
	}
}
