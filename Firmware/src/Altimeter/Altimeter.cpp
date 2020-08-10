#include "Altimeter.h"

Altimeter::Altimeter(float tolerance)
{
	this->tolerance = tolerance;
}

bool Altimeter::setup()
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
	data.groundAltitude = barometricSensor.readAltitudeFeets();

	return true;
}

altimeter_data Altimeter::getData()
{
	float currentAltitude = barometricSensor.readAltitudeFeets() - data.groundAltitude;

	// Only update variables if the value is above or below the tolerance
	if (currentAltitude - data.deltaAltitude >= tolerance)
	{
		// Set variables
		data.altitude = currentAltitude;
		data.speed = (data.deltaAltitude - data.altitude) * 0.3048f;
	}

	// Set delta altitude
	data.deltaAltitude = data.altitude;

	return data;
}
