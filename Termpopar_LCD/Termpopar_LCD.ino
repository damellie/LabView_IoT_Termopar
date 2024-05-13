//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <LiquidCrystal_I2C.h>

#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;
int vccPin = 3;
int gndPin = 2;
float temperatura;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
// make a cute degree symbol
uint8_t degree[8]  = {140,146,146,140,128,128,128,128};


void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  
  // wait for MAX chip to stabilize
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);

  lcd.begin(16, 2);
  lcd.createChar(0, degree);
  // wait for MAX chip to stabilize
  delay(1000);
}


void loop()
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  
  // go to line #1
  lcd.setCursor(0,1);
  temperatura = thermocouple.readCelsius();
  lcd.print(temperatura);
  Serial.print(String(temperatura));
  Serial.print("\n");
#if ARDUINO >= 100
  lcd.write((byte)0);
#else
  lcd.print(0, BYTE);
#endif
  lcd.print("C ");
 
  delay(1000);

}
