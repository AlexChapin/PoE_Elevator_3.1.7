#pragma config(Sensor, dgtl1,  FloorLight1,    sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  FloorLight2,    sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  FloorLight3,    sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,  CallFloor1,     sensorTouch)
#pragma config(Sensor, dgtl5,  CallFloor2,     sensorTouch)
#pragma config(Sensor, dgtl6,  CallFloor3,     sensorTouch)
#pragma config(Sensor, dgtl7,  SendFloor1,     sensorTouch)
#pragma config(Sensor, dgtl8,  SendFloor2,     sensorTouch)
#pragma config(Sensor, dgtl9,  SendFloor3,     sensorTouch)
#pragma config(Sensor, dgtl10, ElevatorEncoder, sensorQuadEncoder)
#pragma config(Motor,  port2,  ElevateMotor,  tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int FastMove = 45;
const int FastMoveDown = 45;
const int MoveSpeed = 30;
const int MoveSpeedDown= 29;
const int SlowSpeedUp = 25;
const int SlowSpeedDown = 10;
//Movement Speeds For Different Controller States

const int FastError = 40;
const int NormalError = 20;
const int SlowError = 10;
const int StopError = 3;
//Acceptable Offset For Motor Drive Commands

const int Level1Setpoint = -10;
const int Level2Setpoint = -165;
const int Level3Setpoint = -347;
//Encoder Setpoints For Each Target Floor

const int LEDThresholdFloor1 = -131;
const int LEDThresholdFloor3 = -279.5;
//Encoder Thresholds That Toggle LEDs On And Off

int TargetPose=0;
//Creates Target Setpoint Variable
int BlinkCount=0;
//Provides Counting For Blink Animation

task main() {
 startMotor(ElevateMotor,15);
//Drives Motor To 0 Position
 while(BlinkCount<10){
 turnLEDOn(FloorLight1);turnLEDOn(FloorLight2);turnLEDOn(FloorLight3);
 wait(.25);
 turnLEDOff(FloorLight1);turnLEDOff(FloorLight2);turnLEDOff(FloorLight3);
 wait(.25);
 BlinkCount=BlinkCount+1;
}
//Blink LEDS While Zeroing Setpoints
 stopMotor(ElevateMotor);
 //Stops Motor After Reaching 0 Position
 SensorValue(ElevatorEncoder) = 0;
 //Zeros the Encoder
 TargetPose=Level1Setpoint;
 //Sets The Target Pose To The First Floor
	while (true) {

		if (SensorValue[ElevatorEncoder] > (TargetPose-StopError) && (SensorValue[ElevatorEncoder] < (TargetPose+StopError))){
		stopMotor(ElevateMotor);
		}//If Current Pose Is Within 3 Clicks In Either Direction, Stop The Motor

		if (SensorValue[ElevatorEncoder] < (TargetPose-FastError)) {
		startMotor(ElevateMotor, FastMoveDown);
		}//If Current Pose Is Farther Than 40 Clicks Up From Target Pose, Run The Motor Down Fast

		if (SensorValue[ElevatorEncoder] > (TargetPose+FastError)) {
		startMotor(ElevateMotor, -FastMove);
		}//If Current Pose Is Farther Than 40 Clicks Down From Target Pose, Run The Motor Up Fast

		if (SensorValue[ElevatorEncoder] < (TargetPose-NormalError)) {
		startMotor(ElevateMotor, MoveSpeedDown);
		}//If Current Pose Is Farther Than 20 Clicks Up From Target Pose, Run The Motor Down

		if (SensorValue[ElevatorEncoder] > (TargetPose+NormalError)) {
		startMotor(ElevateMotor, -MoveSpeed);
		}//If Current Pose Is Farther Than 20 Clicks Down From Target Pose, Run The Motor Up

		if (SensorValue[ElevatorEncoder] < (TargetPose-SlowError)) {
		startMotor(ElevateMotor, SlowSpeedDown);
		}//If Current Pose Is Farther Than 10 Clicks Up From Target Pose, Run The Motor Down Slowly

		if (SensorValue[ElevatorEncoder] > (TargetPose+SlowError)) {
		startMotor(ElevateMotor, -SlowSpeedUp);
		}//If Current Pose Is Farther Than 10 Clicks Down From Target Pose, Run The Motor Up Slowly

		if (SensorValue[CallFloor1]==1) {
		TargetPose = Level1Setpoint;
		}
		if (SensorValue[CallFloor2]==1) {
		TargetPose = Level2Setpoint;
		}
		if (SensorValue[CallFloor3]==1) {
		TargetPose = Level3Setpoint;
		}
		//Bind Bump Switches To Set Values For Target Pose

		if (SensorValue[SendFloor1]==1) {
		TargetPose = Level1Setpoint;
		}
		if (SensorValue[SendFloor2]==1) {
		TargetPose = Level2Setpoint;
		}
		if (SensorValue[SendFloor3]==1) {
		TargetPose = Level3Setpoint;
		}
		//Bind Limit Switches To Set Values For Target Pose

		if (SensorValue(ElevatorEncoder)<LEDThresholdFloor1){turnLEDOff(FloorLight1);}
		if (SensorValue(ElevatorEncoder)>LEDThresholdFloor1){turnLEDOff(FloorLight2);}
		if (SensorValue(ElevatorEncoder)<LEDThresholdFloor3){turnLEDOff(FloorLight2);}
		if (SensorValue(ElevatorEncoder)>LEDThresholdFloor3){turnLEDOff(FloorLight3);}
		//Conditions For LEDs To Turn Off


		if (SensorValue(ElevatorEncoder)>LEDThresholdFloor1){
			turnLEDOn(FloorLight1);
		}//If Above Threshold For LED1 Turn It On

		if (SensorValue(ElevatorEncoder)<LEDThresholdFloor1 && SensorValue(ElevatorEncoder)>LEDThresholdFloor3){
			turnLEDOn(FloorLight2);
		}//If Between Thresholds For Floor 1 And Floor 3 Turn LED2 On

		if (SensorValue(ElevatorEncoder)<LEDThresholdFloor3){
			turnLEDOn(FloorLight3);
		}//If Below Threshold For LED3 Turn It On


}
}
