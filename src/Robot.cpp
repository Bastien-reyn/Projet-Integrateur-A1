#include "Robot.h"

#define I2C_ADDRESS 0x0f


Robot::Robot()
{
	_correct = 0;
	lineFinder = new LineFinder();
	// Serial.begin(9600);

	Serial.println(Motor.begin(I2C_ADDRESS));
}

ERobotState Robot::followLine(ECatchLine state)
{
	long unsigned int t1 = millis();
	ERobotState returnState = ERobotState::FOLLOWING;

	switch (state)
	{

	case ECatchLine::TurnLeft:
		_correct -= 40;
		returnState = ERobotState::LEFT_TURN;
		break;
	case ECatchLine::Left:
		_correct -= 10;
		break;
	case ECatchLine::Straight:
		break;
	case ECatchLine::Right:
		_correct += 10;
		break;
	case ECatchLine::TurnRight:
		_correct += 40;
		returnState = ERobotState::RIGHT_TURN;
		break;
	case ECatchLine::Reverse:
		//_correct = 70;
		break;
	case ECatchLine::Error:
		#ifdef DEBUG
			Serial.println("Exception: there is one exception in LineFinder::find() a case does not fit the conditions");
		#endif
		break;
	case ECatchLine::LeftOrRight:
		returnState = ERobotState::LEFT_AND_RIGHT_TURN;
		break;
	default:
		#ifdef DEBUG
			Serial.println("Error: LineFinder::find() return is not in the enumeration ");
		#endif
		break;
	}

	if (_correct > 70)
	{
		_correct = 70;
	}
	else if (_correct < -70)
	{
		_correct = -70;
	}
	motorDriverMove((70 + _correct), (70 - _correct));
	if (millis()<t1+20)
	return returnState;
}

void Robot::motorDriverMove(int left, int right)
{
	Motor.speed(MOTOR1, left);
	Motor.speed(MOTOR2, right);
}