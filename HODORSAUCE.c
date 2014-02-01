#pragma config(Sensor, S1,     touchysensor,   sensorTouch)
#pragma config(Sensor, S2,     ultrasonarderp, sensorSONAR)
#pragma config(Sensor, S3,     derpylight,     sensorLightActive)
//trololololololo
task main()
{
while(true)
	{
	if(SensorValue[ultrasonarderp]>=30)
		{
		if(SensorValue[touchysensor]==1)
			{
			motor[motorA]=75;
			motor[motorB]=75;

			if(SensorValue[ultrasonarderp]<=30||SensorValue[touchysensor]!=1)
			{motor[motorA]=0;
		 	 motor[motorB]=0;}


			}
			else
			motor[motorA]=0;
			motor[motorB]=0;

			if(SensorValue[derpylight]<=44)
			{motor[motorA]=50;
				motor[motorB]=0;}
			else
					motor[motorA]=0;
					motor[motorB]=50;
		//}
					/*if(SensorValue[ultrasonarderp]<=30||SensorValue[touchysensor]!=1)
					{
						motor[motorA]=0;
						motor[motorB]=0;
					}
					else
					{
						motor[motorA]=75;
						motor[motorB]=75;
					}*/
	}
}
}
