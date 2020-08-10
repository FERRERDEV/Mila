#pragma once

// Sensors
#include "BMP280.h"

/**
 * Struct to hold the altimeter data.
 */
struct altimeter_data
{
	/* Reference altitude of the ground. It will be set on initialization. */
	float groundAltitude = 0.f;
	/* Current altitude from the ground. */
	float altitude = 0.f;
	/* Previous altitude read. */
	float deltaAltitude = 0.f;
	/* Vertical speed in m/s. */
	float speed = 0.f;
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
	 * @brief  Check the sensor and initialize the altimeter.
	 * @return true on successful initialization.
	 */
	bool setup();

	/*!
	 * @brief  Calculates and return all the altitudes data.
	 * @return Altimeter data.
	 */
	altimeter_data getData();
	
private:
	/* Barometric sensor. */
	BMP280 barometricSensor;

	/* Altimeter tolerance config. */
	float tolerance;

	/* Altimeter data. */
	altimeter_data data;
};

