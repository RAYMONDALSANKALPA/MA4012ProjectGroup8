// enum
//enum Orientation
//{
//    NORTH,              // 0
//    NORTH_EAST,         // 1
//    EAST,               // 2
//    SOUTH_EAST,         // 3
//    SOUTH,              // 4
//    SOUTH_WEST,         // 5
//    WEST,               // 6
//    NORTH_WEST,         // 7
//    INVALID_COMBINATION // 8
//};

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
float avg_bl;
float avg_bs;
float total_bl;
float total_bs;
int NUM_READINGS = 100;

task sensor_calibration(){
	while(1){

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
	}
	avg_efd = total_efd/NUM_READINGS;
	avg_ebd = total_ebd/NUM_READINGS;
	avg_bl = total_bl/NUM_READINGS;
	avg_bs = total_bs/NUM_READINGS;

	sleep(100);
	}
}

// sharp sensor parameter
int top_detection_value = 357;
int bottom_detection_value = 100;

// ball status
int ball_found = 0;
//int ball_collected = 0;

//// compass status
//int compass_status;
//int goal_compass_status;

//// limit_switch_status
//int dispense_limit_status;
//int dispense_limit_switch_voltage; // analog

//// line_sensor_status
//BoundarySide line_sensor_status;

//// spin_search alternation
//int spin_CCW = 0;

void scan_ball()
{
    if (avg_bl < bottom_detection_value && avg_efd > top_detection_value)
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

// void read_compass()
// {
//     int pin1 = SensorValue(compass1);
//     int pin2 = SensorValue(compass2);
//     int pin3 = SensorValue(compass3);
//     int pin4 = SensorValue(compass4);
//     int combination = pin1 * 1000 + pin2 * 100 + pin3 * 10 + pin4;

//     switch (combination)
//     {
//     case 1110:
//         compass_status = NORTH;
//         return;
//     case 1100:
//         compass_status = NORTH_EAST;
//         return;
//     case 1101:
//         compass_status = EAST;
//         return;
//     case 1001:
//         compass_status = SOUTH_EAST;
//         return;
//     case 1011:
//         compass_status = SOUTH;
//         return;
//     case 0011:
//         compass_status = SOUTH_WEST;
//         return;
//     case 0111:
//         compass_status = WEST;
//         return;
//     case 0110:
//         compass_status = NORTH_WEST;
//         return;
//     default:
//         compass_status = INVALID_COMBINATION;
//         return;
//     }
// }
