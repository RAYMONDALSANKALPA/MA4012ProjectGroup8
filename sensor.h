//enum BoundarySide
//{
//    FRONT_LEFT,
//    FRONT_RIGHT,
//    BACK_LEFT,
//    BACK_RIGHT,
//    NO_BOUNDARY_DETECTED
//};

// converting sensor analog value to cm and avg it
//int enemy_front_dist;
//int enemy_back_dist;
float avg_efd;
float avg_ebd;
float total_efd;
float total_ebd;

//int ball_long;
//int ball_short;
float avg_bl = 1000;
float avg_bs;
float total_bl;
float total_bs;
int NUM_READINGS = 1;

task sensor_calibration(){
	while(1){
	int ball_collected_limit = SensorValue(ball_limit);
	total_efd = 0;
	total_ebd = 0;
	total_bl = 0;
	total_bs = 0;

	//enemy_front_dist = SensorValue(sharp_front_top);
	//enemy_back_dist = SensorValue(sharp_back_top);
	//ball_long = SensorValue(sharp_bl)
	//ball_short = SensorValue(sharp_bs)

	for (int i = 0; i <= NUM_READINGS; i++) {
		total_efd += 29.98*pow((SensorValue(sharp_front_top)*0.0012207031), -1.173);
		total_ebd += 29.98*pow((SensorValue(sharp_back_top)*0.0012207031), -1.173);
		total_bl += 29.98*pow((SensorValue(sharp_bl)*0.0012207031), -1.173);
		total_bs += 5.2819*pow((SensorValue(sharp_bs)*0.0012207031), -1.161);
		delay(35);
	}
	avg_efd = total_efd/NUM_READINGS;
	avg_ebd = total_ebd/NUM_READINGS;
	avg_bl = total_bl/NUM_READINGS;
	avg_bs = total_bs/NUM_READINGS;
	 //writeDebugStreamLine("%f", avg_bl);

	//sleep(100);
	}
}

// sharp sensor parameter
int top_detection_value = 357;
int bottom_detection_value = 75;

// ball status
int ball_found = 0;
//int ball_collected = 0;

//// limit_switch_status
//int dispense_limit_status;
//int dispense_limit_switch_voltage; // analog

//// line_sensor_status
//BoundarySide line_sensor_status;

//// spin_search alternation
//int spin_CCW = 0;

void scan_ball()
{
    if (avg_bl < bottom_detection_value)
    {
            ball_found = 1;
            return;
    }
   	else
    {
        ball_found = 0;
        return;
    }
}

int read_compass()			// read compass value and return the direction
{
	// Convention of choosing direction
	//    NORTH,              // 0
	//    NORTH_EAST,         // 1
	//    EAST,               // 2
	//    SOUTH_EAST,         // 3
	//    SOUTH,              // 4
	//    SOUTH_WEST,         // 5
	//    WEST,               // 6
	//    NORTH_WEST,         // 7
	int north = 0;
	int northeast = 1;
	int east = 2;
	int southeast = 3;
	int south = 4;
	int southwest = 5;
	int west = 6;
	int northwest = 7;
	// TODO: fix this stupid code
    int pin1 = SensorValue(compass1);
    int pin2 = SensorValue(compass2);
    int pin3 = SensorValue(compass3);
    int pin4 = SensorValue(compass4);
    int combination = pin1 * 1000 + pin2 * 100 + pin3 * 10 + pin4;
	int compass_dir;

	// if (combination == 1011){ // south
	// 	compass_dir = south;
	// }
	// else{
	// 	compass_dir = 0;
	// }

	// convert the above if else statement to switch case
	switch (combination){
		case 1100:
			compass_dir = north;
			break;
		case 1101:
			compass_dir = northeast;
			break;
		case 1010:
			compass_dir = east;
			break;
		case 1001:
			compass_dir = southeast;
			break;
		case 1011:
			compass_dir = south;
			break;
		case 0011:
			compass_dir = southwest;
			break;
		case 0110:
			compass_dir = west;
			break;
		case 1110:
			compass_dir = northwest;
			break;
		//default:
		//	compass_dir = 100; // error!
		//	break;
	}

	return compass_dir;
}

//void compass_test(){
//	while(1){
//		int compass_dir = read_compass();
//		printf("Compass direction: %d\n", compass_dir);
//		wait1Msec(1000);
//	}
//}

//void read_short_sharp()
//{
//    dist_back = SensorValue(sharp_short);
//    return;
//}

// void read_dispense_limit_switch()
// {
//     // analog limit switch
//     dispense_limit_switch_voltage = SensorValue(dispense_limit_switch);
//     if (dispense_limit_switch_voltage != 0)
//     {
//         dispense_limit_status = 1;
//         return;
//     }
//     else
//     {
//         dispense_limit_status = 0;
//         return;
//     }
// }

// void is_ball_on_vehicle()
// {
//     if (SensorValue(ball_collection_limit) == 0)
//     {
//         ball_collected = 1;
//         return;
//     }
//     else
//     {
//         ball_collected = 0;
//         return;
//     }
// }

//void scan_boundary()
//{
//    int frontLeft = SensorValue(front_l_line);
//    int frontRight = SensorValue(front_r_line);
//    int backLeft = SensorValue(back_l_line);
//    int backRight = SensorValue(back_r_line);

//    if (frontLeft < 800)
//    {
//        line_sensor_status = FRONT_LEFT;
//        return;
//    }
//    else if (frontRight == 0)
//    {
//        line_sensor_status = FRONT_RIGHT;
//        return;
//    }
//    else if (backLeft == 0)
//    {
//        line_sensor_status = BACK_LEFT;
//        return;
//    }
//    else if (backRight == 0)
//    {
//        line_sensor_status = BACK_RIGHT;
//        return;
//    }
//    else
//    {
//        line_sensor_status = NO_BOUNDARY_DETECTED;
//        return;
//    }
//}
