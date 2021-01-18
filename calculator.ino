// include data.h file for all libraries and constants
#include "data.h"

// create a DHT object
dht DHT;

/*
* humidity and temperature variables are created
* in this scope as they are to be manipulated
*/
int humidity = 0, temperature = 0;

// create an LCD object
LiquidCrystal lcd = LiquidCrystal(RS, E, D4, D5, D6, D7);

// setup code to run once
void setup()
{
  // begin the serial monitor at a 9600 baud rate
  Serial.begin(9600);
  // set the buzzer pin as OUTPUT
  pinMode(buzzPin, OUTPUT);
  // specify the LCD's number of columns and rows
  lcd.begin(16, 2);
  // run the boot sequence
  bootSequence();
}

void loop()
{

  // read the value/input from the DHT temp and humidity sensor
  DHT.read11(dht_apin);

  // set the temperature and humidity variables to read values
  humidity = DHT.humidity;
  temperature = DHT.temperature;

  // set the cursor on the first column and the first row
  lcd.setCursor(0, 0);
  // print the humidity values (as a percent (%))
  lcd.print("Humidity:");
  lcd.print(humidity);
  lcd.print("%");
  // set the cursor on the third column and the second row:
  lcd.setCursor(0, 1);
  // print the temperature values (in terms of degrees (C))
  lcd.print("Temperature:");
  lcd.print(temperature);
  lcd.print("C");

  // temperature is too hot (27 degrees+) set off the beeper
  if (temperature >= TOO_HOT)
  {
    digitalWrite(buzzPin, HIGH);
    delay(150);
    digitalWrite(buzzPin, LOW);
  }
  // if the temperature is regulated, keep the beeper off
  else
  {
    digitalWrite(buzzPin, LOW);
  }

  //Wait 1 seconds before accessing sensor again.
  delay(1000); 

}
/*
* a set of beeps (3) totalling 1.95 seconds to
* allow for the user to know the program begins,
* also giving time for the display and sensor to boot up 
*/
void bootSequence()
{
  digitalWrite(buzzPin, HIGH);
  delay(500);
  digitalWrite(buzzPin, LOW);
  delay(150);
  digitalWrite(buzzPin, HIGH);
  delay(500);
  digitalWrite(buzzPin, LOW);
  delay(150);
  digitalWrite(buzzPin, HIGH);
  delay(500);
  digitalWrite(buzzPin, LOW);
  delay(150);
}