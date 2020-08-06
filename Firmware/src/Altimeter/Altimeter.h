#pragma once

// Includes
#include "BMP280.h"

/**
 * Modes to control the jump state.
 */
enum modes
{
	Ground,
	Plane,
	Freefall
};

/**
 * Struct to hold the altimeter data.
 */
struct data
{
	/* Reference altitude of the ground. It will be set on initialization. */
	float groundAltitude = 0.f;
	/* Current altitude from the ground. */
	float altitude = 0.f;
	/* Previous altitude read. */
	float deltaAltitude = 0.f;
	/* Vertical speed. */
	float speed = 0.f; // m/s
	/* Mode to control the jump state. */
	modes mode = modes::Ground;
};

/**
 * Class to hold the altimeter functionality.
 */
class Altimeter
{
public:
	/*!
	 * @brief  Constructor using a tolerance value.
	 * @param  Tolerance in feet.
	 */
	Altimeter(float tolerance);

	/*!
	 * @brief  Check and initialize the altimeter.
	 * @return true on successful initialization.
	 */
	bool begin();

	/*!
	 * @brief  Calculates and return all the altitudes data.
	 * @return Altimeter data.
	 */
	data getData();
private:
	/* Barometric sensor. */
	BMP280 barometricSensor;

	/* Altimeter tolerance config. */
	float _tolerance;

	/* Altimeter data. */
	data _data;
};

