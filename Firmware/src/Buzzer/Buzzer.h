#pragma once

// Includes
#include "Notes.h"

/**
 * Struct to hold a cue data.
 */
struct cue
{
	int Tone;
	int Duration;
};

/**
 * Struct to hold an alarm data.
 */
struct alarm
{
	int Lenght;
	cue Cue[3];
	float Time;
};

// Defined alarms tones
static alarm HARDWARE_OK_ALARM		= { 3, {{NOTE_C6, 50}, {NOTE_C6, 50}, {NOTE_C6, 50 }}, 100 };
static alarm HARDWARE_FAILURE_ALARM = { 3, {{NOTE_C6, 1000}, {NOTE_D8, 1000}, {NOTE_C6, 1000 }}, 100 };
static alarm SEATBELT_ALARM			= { 3, {{NOTE_A5, 250}, {NOTE_A6, 250}, {NOTE_A6, 250 }}, 250 };
static alarm BREAKOFF_ALARM			= { 3, {{NOTE_C6, 500}, {NOTE_D8, 500}, {NOTE_C6, 500 }}, 500 };
static alarm PULL_ALARM				= { 3, {{NOTE_C7, 50}, {NOTE_C7, 50}, {NOTE_C7, 50 }}, 75 };
static alarm WARNING_ALARM			= { 3, {{NOTE_C6, 150}, {NOTE_C5, 150}, {NOTE_C6, 150 }}, 100 };

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
	Buzzer(int BUZZER_PIN);

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
	/* Const buzzer pin. */
	int BUZZER_PIN;

	/* State to control infinite alarms */
	bool bInfiniteAlarm;
};
