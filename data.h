// include libraries for display and sensor
#include "LiquidCrystal.h"
#include "dht.h"

// define constants for pins
#define dht_apin A0 // analog 0 for the temperature sensor
#define buzzPin 12 // digital 12 for the button

// define lcd display pins
#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

// define the temperature that is "too hot" and will set off the beeper
#define TOO_HOT 37

extern String message = " Go and open a window or door! Let's decrease this temperature!";
#define msgLength message.length()