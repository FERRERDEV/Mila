// Buzzer
#include "Buzzer.h"

// Arduino
#include "Arduino.h"

// Mila
#include "Mila.h"

Buzzer::Buzzer(int buzzerPin)
{
	// Assign the buzzer pin.
	this->buzzerPin = buzzerPin;
}

void Buzzer::playAlarm(alarm alarmToPlay, int loops)
{
	bInfiniteAlarm = loops == -1;

	while (bInfiniteAlarm)
	{
		for (int loop = loops; loop - loops >= 0; loop--)
		{
			if (bInfiniteAlarm)
				loop++;

			for (int i = 0; i < alarmToPlay.Lenght; i++)
			{
				tone(buzzerPin, alarmToPlay.Cue[i].Tone, alarmToPlay.Cue[i].Duration);
				delay(alarmToPlay.Time);
			}
			delay(alarmToPlay.Time);
		}
	}
}

void Buzzer::stopAlarm()
{
	bInfiniteAlarm = false;
}
