// Includes
#include "Arduino.h"
#include "Mila.h"

Mila* mila;

/*!
 * Setup method, executed on startup.
 */
void setup()
{
	mila = new Mila();
	mila->setup();
}

/*!
 * Loop method
 */
void loop() 
{
	mila->run();
}