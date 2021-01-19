// include data.h file for all libraries and constants
#include "data.h"

// create a DHT object
dht DHT;

/*
* humidity and temperature variables are created
* in this scope as they are to be manipulated
*/
int humidity = 0, temperature = 0;

// variables that will be used in the manipulation of the Strings
int end = 0;
String displayMessage = "";

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

// code to loop through
void loop()
{
  // call a method to read the temperature and humidity info
  getReading();

  /*
  * while the sensor reads the already defined "TOO_HOT"
  * value run thorugh the help message, beeper, etc 
  */
  hotAction();

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

/*
* Get a reading from the sensor to show
* the Humidity (%) and the Temperature (degrees C)
* on the LCD display, using both its rows
*/
void getReading()
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
  Serial.println(humidity);
  lcd.print("%");
  // set the cursor on the third column and the second row:
  lcd.setCursor(0, 1);
  // print the temperature values (in terms of degrees (C))
  lcd.print("Temperature:");
  lcd.print(temperature);
  Serial.println(temperature);
  lcd.print("C");
}

/*
* A set of actions the robot should do if the temperature
* gets too hot (i.e setting of a beeper, help message, etc).
*/
void hotAction()
{
  // temperature is too hot (27 degrees+) set off the actions
  if (temperature >= TOO_HOT)
  {
    for (int start = 0; start < msgLength; start++)
    {
      /*
      * read the sensor to retrieve the current
      * temperature to display and compare
      */
      DHT.read11(dht_apin);
      temperature = DHT.temperature;

      // print the current temperature on the first row
      lcd.setCursor(0, 0);
      lcd.print("That's hot!->");
      lcd.print(temperature);
      lcd.print("C");

      // begin printing to the second row
      lcd.setCursor(0, 1);
      // use the "end" variable as an index for help text printing
      end = start + 15;

      /*
      * loop the index around if the 
      * sensor has not cooled down yet
      */
      if (end == (msgLength - 1))
      {
        start = 0;
        end = start + 15;
      }

      // shorten the message constant to make it fit on the display
      displayMessage = message.substring(start, end);

      //print the message, sliding along every 0.65 seconds
      lcd.print(displayMessage);
      delay(650);

      // beep after every letter
        digitalWrite(buzzPin, HIGH);
        delay(30);
        digitalWrite(buzzPin, LOW);

      // if the temperature is back to a regulated level, exit the loop
      if (temperature < TOO_HOT)
      {
        start = msgLength;
        lcd.clear();
      }
    }
  }
  // if the temperature is regulated, keep the beeper off
  else
  {
    digitalWrite(buzzPin, LOW);
  }
}