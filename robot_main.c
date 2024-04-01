#pragma config(Sensor, in2,    obstaclesensor, sensorAnalog)
#pragma config(Sensor, in7,    ballsensor,     sensorAnalog)
#pragma config(Sensor, dgtl12, ledlight,       sensorDigitalOut)
#pragma config(Motor,  port2,           rightmotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           dispensor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           conveyor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftmotor,     tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "movement.c"
#include "sensing.c"

task main()
{
	// For now, testing motors
	movement_test();
	//right_motor_test();
	//left_motor_test();
	//conveyor_test();
	//dispensor_test();

	while(){
		//searching();
	}
}
