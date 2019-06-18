#include "Robot.h"

#define I2C_ADDRESS 0x0f

Robot::Robot()
{
	_correct = 0;
	lineFinder = new LineFinder();
	// Serial.begin(9600);
	lastCorrectionTime = millis();
	Serial.println(Motor.begin(I2C_ADDRESS));
}

ERobotState Robot::followLine(ECatchLine state)
{
	ERobotState returnState = ERobotState::FOLLOWING;

	switch (state)
	{

	case ECatchLine::TurnLeft:
		_correct = -70;
		returnState = ERobotState::LEFT_TURN;
		break;
	case ECatchLine::Left:
		_correct = -30;

		break;
	case ECatchLine::Straight:
		/*if (_correct > 0)
		{
			correct(-5);
		}
		else if (_correct < 0)
		{
			correct(5);
		}*/
		_correct = 0;
		break;
	case ECatchLine::Right:
		_correct = 30;
		break;
	case ECatchLine::TurnRight:
		_correct = 70;
		returnState = ERobotState::RIGHT_TURN;
		break;
	case ECatchLine::Reverse:
		//_correct = 70;
		break;
	case ECatchLine::Error:
#ifdef DEBUG
		Serial.print("	Exception: there is one exception in LineFinder::find() a case does not fit the conditions.");
#endif
		break;
	case ECatchLine::LeftOrRight:
		returnState = ERobotState::LEFT_AND_RIGHT_TURN;
		break;
	default:
#ifdef DEBUG
		Serial.print("	Error: LineFinder::find() return is not in the enumeration.");
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
	return returnState;
}

void Robot::motorDriverMove(int left, int right)
{
	Motor.speed(MOTOR1, left);
	Motor.speed(MOTOR2, right);
}

void Robot::correct(int correction)
{
	if (lastCorrectionTime - millis() >= 50)
	{
		lastCorrectionTime = millis();
		_correct += correction;
	}
#ifdef DEBUG
	if (lastCorrectionTime - millis() > 200)
	{
		Serial.print("	Correction trop longue.");
	}
#endif
}