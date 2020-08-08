// Mila
#include "Mila.h"

// Arduino
#include "Arduino.h"

// Components
#include "Altimeter/Altimeter.h"
#include "Buzzer/Buzzer.h"

Mila::Mila()
{
    // Create components
    altimeter = new Altimeter(ALTIMETER_TOLERANCE);
    buzzer = new Buzzer(BUZZER_PIN);
}

void Mila::setup()
{
    // Pins setup
	pinMode(BUZZER_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);

	// Altimeter initialization
	while (!altimeter->setup())
	{
		buzzer->playAlarm(HARDWARE_FAILURE_ALARM);
	}

	digitalWrite(LED_PIN, HIGH);
	buzzer->playAlarm(HARDWARE_OK_ALARM);
}

void Mila::run()
{
    altimeter_data data = altimeter->getData();

    mode = getMode(data);

    switch (mode)
    {
    case modes::Ground:
        if (bJumpStarted)
        {
            reset();
        }
        break;
    case modes::Plane:
        if (data.altitude >= SEATBELT_ALTITUDE && !bSeatbelt)
        {
            buzzer->playAlarm(SEATBELT_ALARM, SEATBELT_ALARM_LOOPS);
            bSeatbelt = true;
        }
        break;
    case modes::Freefall:
        if (data.altitude <= BREAKOFF_ALTITUDE && !bBreakoff)
        {
            buzzer->playAlarm(BREAKOFF_ALARM, BREAKOFF_ALARM_LOOPS);
            bBreakoff = true;
        }

        if (data.altitude <= PULL_ALTITUDE && !bPull)
        {
            buzzer->playAlarm(PULL_ALARM, PULL_ALARM_LOOPS);
            bPull = true;
        }

        if (data.altitude <= WARNING_ALTITUDE)
        {
            if (data.speed >= WARNING_SPEED && !bWarning)
            {
                buzzer->playAlarm(WARNING_ALARM, WARNING_ALARM_LOOPS);
                bWarning = true;
            }

            if (data.speed < WARNING_SPEED && bWarning)
            {
                buzzer->stopAlarm();
            }
        }

        break;
    default:
        break;
    }

    delay(TIME_BETWEEN_LECTURES);
}

void Mila::reset()
{
	bJumpStarted = false;
	bSeatbelt = false;
	bBreakoff = false;
	bPull = false;
	bWarning = false;
}

modes Mila::getMode(altimeter_data data)
{
    if (data.altitude <= data.deltaAltitude + 20)
    {
        return modes::Ground;
    }

    if (data.altitude >= data.deltaAltitude)
    {
        return modes::Plane;
    }
    else
    {
        return modes::Freefall;
    }
}