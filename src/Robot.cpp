#include "Robot.h"

#define I2C_ADDRESS 0x0f
#define Kp 0.015
#define Ki 0
#define Kd 0
double P = 0;
double I = 0;
double D = 0;


Robot::Robot()
{
	_correct = 0;
	// Serial.begin(9600);
	lastCorrectionTime = millis();
	lastTurn = millis() + 500;
	actualLineState = ECatchLine::Straight;
	lastError = 0;
	error = 0;
	baseError = 0;
	turning = 0;
	lasttimeturn = 0;
	Serial.println(Motor.begin(I2C_ADDRESS));
	lineFinder = new LineFinder();
}

ERobotState Robot::followLine()
{
	ECatchLine state = lineFinder->find();
	ERobotState returnState = ERobotState::FOLLOWING;

	switch (state)
	{

	// TOURNER A GAUCHE !!!!
	case ECatchLine::TurnLeft:
		//_correct = -50;
		returnState = ERobotState::LEFT_TURN;
		break;

	// CORRECTION A GAUCHE !!!!
	case ECatchLine::Left:
		_correct = -30;

		break;

	// TOUT DROIT !!!!
	case ECatchLine::Straight:
		_correct = 0;
	
		/*if (_correct > 0)
		{
			correct(-5);
		}
		else if (_correct < 0)
		{
			correct(5);
		}*/
		
		break;

	// CORRECTION A DROITE !!!!
	case ECatchLine::Right:
		_correct = 30;
		break;

	// TOURNER A DROITE !!!!
	case ECatchLine::TurnRight:
		//_correct = 50;
		returnState = ERobotState::RIGHT_TURN;
		break;

	// RETOUR INUTILISE !!!!
	case ECatchLine::Reverse:
		//_correct = 70;
		break;

	// ERREUR !!!!
	case ECatchLine::Error:
#ifdef DEBUG
		Serial.print("	Exception: there is one exception in LineFinder::find() a case does not fit the conditions.");
#endif
		break;

	// INTERSECTION !!!!
	case ECatchLine::LeftOrRight:
		returnState = ERobotState::LEFT_AND_RIGHT_TURN;
		//_correct = 70;
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


ERobotState Robot::takeTurn(ERobotState state){
	int left = 0;
	int right = 0;
    
    if (state == ERobotState::LEFT_TURN)
    {
      right = 90;
      left = 0;
    }
    else if (state == ERobotState::RIGHT_TURN)
    {
      left = 90;
      right = 0;
    }

	else
	{
		return FOLLOWING;
	}
	
    motorDriverMove((left), (right));
    delay(250);

    while (lineFinder->find() != ECatchLine::Straight)
    {
	}
	  lastTurn = millis();
	
	return ERobotState::FOLLOWING;
}

void Robot::motorDriverMove(int left, int right)
{
	Motor.speed(MOTOR1, left);
	Motor.speed(MOTOR2, right);
}

void Robot::correct(int correction)
{
	if (millis() - lastCorrectionTime >= 50)
	{
		lastCorrectionTime = millis();
		_correct += correction;
	}
	#ifdef DEBUG
		if (millis() - lastCorrectionTime > 200)
		{
			Serial.print("	Correction trop longue.");
		}
	#endif
}


ERobotState Robot::followCenterLinePID(ECatchLine state)
{
	ERobotState returnState = ERobotState::FOLLOWING;
	

	switch (state)
	{
	case ECatchLine::Left:
		if (actualLineState != state)
		{
			baseErrorTime = millis();
			actualLineState = state;
			baseError = -1;
		}
		break;
	case ECatchLine::Straight:
		baseError = 0;
		actualLineState = state;
		break;
	case ECatchLine::Right:
		if (actualLineState != state)
		{
			baseErrorTime = millis();
			actualLineState = state;
			baseError = 1;
		}
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
	correctPID(baseError);
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

void Robot::correctPID(int baseError)
{
	error = (millis() - baseErrorTime) * baseError;

	P = error;
	I = I + error;
	D = error-lastError;
	_correct = (Kp*P) + (Ki*I) + (Kd*D);
	lastError = error;
}