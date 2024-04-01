// ! This program has all the sensing capabilities

int search_threshold = 445;
int collection_threshold = 1300;

// ball sensor

void light_blink_simple(){
    SensorValue[ledlight] = 1;
    wait1Msec(500);
    SensorValue[ledlight] = 0;
    wait1Msec(500);
    SensorValue[ledlight] = 1;
    wait1Msec(500);
    SensorValue[ledlight] = 0;
    wait1Msec(500);
}

void closing(){
    closing_movement_simple();
    if(SensorValue[ballsensor] > collection_threshold){
        // light_blink_simple();
        ball_collection();
        wait1Msec(2000);
    }
}

void searching(){
    search_movement_simple();
    if(SensorValue[ballsensor] > search_threshold){
        // light_blink_simple();       
        wait1Msec(2000);
        closing();
    }
}






