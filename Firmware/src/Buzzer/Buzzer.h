#pragma once

#include "Alarm.h"

/**
 * Class to hold all the buzzer and alarms functionality.
 */
class Buzzer
{
public:
	/*!
	 * @brief  Constructor using a output pin.
	 * @param  Pin to use with the buzzer.
	 */
	Buzzer(int buzzerPin);

	/*!
	 * @brief  Plays a given alarm tone
	 * @param  alarmToPlay Alarm to play.
	 * @param  loops The number of loops to be played. 
	 * -1 result on an infinite loop
	 */
	void playAlarm(alarm alarmToPlay, int loops = 1);

	/*!
	 * @brief  Stops the previous infinite alarm.
	 */
	void stopAlarm();

private:
	/* Output pin to be user with the buzzer instance. */
	int buzzerPin;

	/* State to control infinite alarms. */
	bool bInfiniteAlarm;
};
