#pragma once

// Includes
#include "Altimeter.h"

Altimeter::Altimeter(float _tolerance)
{
	this->_tolerance = _tolerance;
}

bool Altimeter::begin()
{
	// Barometric sensor setup
	if (!barometricSensor.begin())
	{
		// If we reach this point, something is wrong with the hardware.
		return false;
	}

	// Set sensor sampling
	barometricSensor.setSampling(
		BMP280::MODE_NORMAL,								/* Operating Mode. */
		BMP280::SAMPLING_X2,								/* Temp. oversampling */
		BMP280::SAMPLING_X16,								/* Pressure oversampling */
		BMP280::FILTER_X16,									/* Filtering. */
		BMP280::STANDBY_MS_500								/* Standby time. */
	);

	// Set the ground altitude
	_data.groundAltitude = barometricSensor.readAltitudeFeets();

	return true;
}

data Altimeter::getData()
{
	float TickAltitude = barometricSensor.readAltitudeFeets() - _data.groundAltitude;

	// Only set variables if the value is above or below the tolerance
	if (TickAltitude - _data.deltaAltitude >= _tolerance)
	{
		// Set variables
		_data.altitude = TickAltitude;
		_data.speed = (_data.deltaAltitude - _data.altitude) * 0.3048f;

		// Set the jump mode
		if (_data.altitude <= _data.altitude + 20)
		{
			_data.mode = modes::Ground;
		}
		else
		{
			if (_data.altitude >= _data.deltaAltitude)
			{
				_data.mode = modes::Plane;
			}
			else
			{
				_data.mode = modes::Freefall;
			}
		}
	}

	// Save delta altitude
	_data.deltaAltitude = _data.altitude;

	return _data;
}
