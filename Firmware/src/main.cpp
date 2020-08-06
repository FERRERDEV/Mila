// Includes
#include "Altimeter/Altimeter.h"
#include "Buzzer/Buzzer.h"

// Pins config
#define LED_PIN         7
#define BUZZER_PIN      8

// Alarms altitudes config in feets
const float BREAKOFF_ALTITUDE               =	6500.f;
const float PULL_ALTITUDE                   =	4500.f;
const float WARNING_ALTITUDE                =	4000.f;
const float SEATBELT_ALTITUDE               =	1500.f;

// Alarms loops config
const int BREAKOFF_ALARM_LOOPS                    =   6;
const int PULL_ALARM_LOOPS                        =   6;
const int WARNING_ALARM_LOOPS                     =   -1;
const int SEATBELT_ALARM_LOOPS                    =   3;

// Altimeter config
const unsigned int ALTIMETER_TOLERANCE      =   5;
const unsigned int TIME_BETWEEN_LECTURES    =   1000;

// Min speed to consider that we are in freefall. In meters per second.
const float WARNING_SPEED					=	10.f;


// Object initialization
Altimeter altimeter(ALTIMETER_TOLERANCE);
Buzzer buzzer(BUZZER_PIN);

// Played alarms control
bool bSeatbelt;
bool bBreakoff;
bool bPull;
bool bWarning;

// Jump control
bool bJumpStarted;

/*!
 * Setup method, executed on startup.
 */
void setup()
{
	// Pins setup
	pinMode(BUZZER_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);

	// Altimeter initialization
	while (!altimeter.begin())
	{
		buzzer.playAlarm(HARDWARE_FAILURE_ALARM);
	}

	digitalWrite(LED_PIN, HIGH);
	buzzer.playAlarm(HARDWARE_OK_ALARM);
}

void reset()
{
	bJumpStarted = false;
	bSeatbelt = false;
	bBreakoff = false;
	bPull = false;
	bWarning = false;
}

/*!
 * Loop method
 */
void loop() 
{
	data _data = altimeter.getData();

	if (_data.mode != modes::Ground && !bJumpStarted)
	{
		bJumpStarted = true;
	}

	switch (_data.mode)
	{
	case modes::Ground:
		if (bJumpStarted)
		{
			reset();
		}
		break;
	case modes::Plane:
		if (_data.altitude >= SEATBELT_ALTITUDE && !bSeatbelt)
		{
			buzzer.playAlarm(SEATBELT_ALARM, SEATBELT_ALARM_LOOPS);
			bSeatbelt = true;
		}
		break;
	case modes::Freefall:
		if (_data.altitude <= BREAKOFF_ALTITUDE && !bBreakoff)
		{
			buzzer.playAlarm(BREAKOFF_ALARM, BREAKOFF_ALARM_LOOPS);
			bBreakoff = true;
		}

		if (_data.altitude <= PULL_ALTITUDE && !bPull)
		{
			buzzer.playAlarm(PULL_ALARM, PULL_ALARM_LOOPS);
			bPull = true;
		}

		if (_data.altitude <= WARNING_ALTITUDE)
		{
			if (_data.speed >= WARNING_SPEED && !bWarning)
			{
				buzzer.playAlarm(WARNING_ALARM, WARNING_ALARM_LOOPS);
				bWarning = true;
			}

			if (_data.speed < WARNING_SPEED && bWarning)
			{
				buzzer.stopAlarm();
			}
		}

		break;
	default:
		break;
	}

	delay(TIME_BETWEEN_LECTURES);
}