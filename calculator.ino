/* Basic Arduino example code for displaying text on 16x2, 20x4 etc. character LCDs. More info: www.makerguides.com */

// Include the library:
#include "data.h"

dht DHT;



// Create an LCD object. Parameters: (RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);

void setup() {
  // Specify the LCD's number of columns and rows. Change to (20, 4) for a 20x4 LCD:
  lcd.begin(16, 2);
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
}

void loop() {

  DHT.read11(dht_apin);

  // Set the cursor on the third column and the first row, counting starts at 0:
  lcd.setCursor(0, 0);
  // Print the string 'Hello World!':
  lcd.print("H: " + DHT.humidity + " %");
  // Set the cursor on the third column and the second row:
  lcd.setCursor(0, 1);
  // Print the string 'LCD tutorial':
  lcd.print("T: " + DHT.temperature + " C");
    
    delay(5000);//Wait 5 seconds before accessing sensor again.
}