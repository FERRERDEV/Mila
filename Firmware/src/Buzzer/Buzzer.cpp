#pragma once

// Includes
#include "Buzzer.h"
#include "Arduino.h"

Buzzer::Buzzer(int BUZZER_PIN)
{
	// Assign the buzzer pin.
	this->BUZZER_PIN = BUZZER_PIN;
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
				tone(BUZZER_PIN, alarmToPlay.Cue[i].Tone, alarmToPlay.Cue[i].Duration);
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
