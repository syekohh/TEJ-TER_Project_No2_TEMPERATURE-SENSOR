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
#define TOO_HOT 27

// empty String used for providing a readable message on scroll view
extern String emptyToAdd = "                ";
// store the message that is going oto be printed to the display
extern String message = " Open a window or door! Decrease this temp!" + emptyToAdd;
// define the length of the String in terms of an "int" variable
#define msgLength message.length()