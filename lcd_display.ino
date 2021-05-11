// include the library code:
#include <LiquidCrystal.h>

#define water_sensor A0
#define power 7

int value = 0;
double percent = 0;
double maxVal = 180;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");

  Serial.begin(9600);
  pinMode(power, OUTPUT);
  pinMode(water_sensor, INPUT);
  //pinMode(led, OUTPUT);
  digitalWrite(power, LOW);
  
  lcd.setCursor(0, 0);
  lcd.print("Moisture Level:");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);

  digitalWrite(power, HIGH);
  delay(10);
  value = analogRead(water_sensor);
  percent = value / maxVal * 100;
  digitalWrite(power, LOW);

  Serial.print("Sensor value: ");
  Serial.print(value);
  Serial.println();
  
  lcd.setCursor(0, 1);
  lcd.print(percent);

  lcd.setCursor(4, 1);
  lcd.print("%");

  delay(1000);
}
