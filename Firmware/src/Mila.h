// Pins config
#define LED_PIN         7
#define BUZZER_PIN      8

// Alarms altitudes config in feets
const float BREAKOFF_ALTITUDE               =	6500.f;
const float PULL_ALTITUDE                   =	4500.f;
const float WARNING_ALTITUDE                =	4000.f;
const float SEATBELT_ALTITUDE               =	1500.f;

// Alarms loops config
const int BREAKOFF_ALARM_LOOPS                    =   6;
const int PULL_ALARM_LOOPS                        =   6;
const int WARNING_ALARM_LOOPS                     =   -1;
const int SEATBELT_ALARM_LOOPS                    =   3;

// Altimeter config
const float ALTIMETER_TOLERANCE      =   5.f;
const unsigned int TIME_BETWEEN_LECTURES    =   1000;

// Min speed to consider that we are in freefall. In meters per second.
const float WARNING_SPEED					=	10.f;

struct altimeter_data;

/**
 * Modes to control the jump state.
 */
enum modes
{
	Ground,
	Plane,
	Freefall
};

class Mila
{
public:
    /*!
    * @brief  Audible constructor.
    */
    Mila();

    /*!
    * @brief  Audible setup and initialization.
    */
    void setup();

    /*!
    * @brief  Audible loop function.
    */
    void run();

private:
    void reset();

    modes getMode(altimeter_data data); 

private:
    // Components
    class Altimeter* altimeter;
    class Buzzer* buzzer;

    // Mode
    modes mode;

    // Played alarms control
    bool bSeatbelt;
    bool bBreakoff;
    bool bPull;
    bool bWarning;

    // Jump control
    bool bJumpStarted;
};