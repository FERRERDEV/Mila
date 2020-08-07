// Notes
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