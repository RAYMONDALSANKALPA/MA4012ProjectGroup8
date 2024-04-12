// converting sensor analog value to cm and avg it
float avg_efd;
float avg_ebd;
float total_efd;
float total_ebd;

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

	for (int i = 0; i <= NUM_READINGS; i++) {
		total_efd += 29.98*pow((SensorValue(sharp_front_top)*0.0012207031), -1.173);
		total_ebd += 29.98*pow((SensorValue(sharp_back_top)*0.0012207031), -1.173);
		total_bl += 29.98*pow((SensorValue(sharp_bl)*0.0012207031), -1.173);
		total_bs += 5.2819*pow((SensorValue(sharp_bs)*0.0012207031), -1.161);
		delay(30);
	}
	avg_efd = total_efd/NUM_READINGS;
	avg_ebd = total_ebd/NUM_READINGS;
	avg_bl = total_bl/NUM_READINGS;
	avg_bs = total_bs/NUM_READINGS;
	 //writeDebugStreamLine("%f", avg_bl);
	}
}

// sharp sensor parameter
int bottom_detection_value = 100;

// ball status
int ball_found = 0;

void scan_ball()
{
    if (avg_bl < bottom_detection_value)
    {
    		motor_stop();
            ball_found = 1;
			writeDebugStreamLine("%s", "ball found");
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

    int pin1 = SensorValue(compass1);
    int pin2 = SensorValue(compass2);
    int pin3 = SensorValue(compass3);
    int pin4 = SensorValue(compass4);
    int combination = pin1 * 1000 + pin2 * 100 + pin3 * 10 + pin4;
	int compass_dir;

	// convert the above if else statement to switch case
	switch (combination){
		case 1110:
			compass_dir = north;
			break;
		case 1100:
			compass_dir = northeast;
			break;
		case 1101:
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
		case 0111:
			compass_dir = west;
			break;
		case 0110:
			compass_dir = northwest;
			break;
	}

	return compass_dir;
}
