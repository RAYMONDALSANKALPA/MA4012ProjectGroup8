#pragma config(Sensor, dgtl2,    IR_FL,           sensorReflection)
#pragma config(Sensor, dgtl3,    IR_FR,           sensorReflection)
#pragma config(Sensor, dgtl4,    IR_BL,           sensorReflection)
#pragma config(Sensor, dgtl5,    IR_BR,           sensorReflection)

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
