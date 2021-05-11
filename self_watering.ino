// include the library code:
#include <LiquidCrystal.h>

#define water_sensor A0
#define power 7
#define button 8
#define relayModule 6

int buttonState = 0;
boolean currentState = false;
boolean previousState = false;

int value = 0;
int page = 0;
int counter = 0;

long timestamp = 0;
long interval = 259200000;
long timeRemaining = 0;

long waterTimestamp = 0;
long waterTime = 60000;
long waterRemaining = 0;

double percent = 0;
double maxVal = 180;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  Serial.begin(9600);
  pinMode(power, OUTPUT);
  pinMode(water_sensor, INPUT);
  //pinMode(led, OUTPUT);
  digitalWrite(power, LOW);

  pinMode(relayModule, OUTPUT);

  pinMode(button, INPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Moisture Level:");
}

void loop() {
  // Read from sensor
  digitalWrite(power, HIGH);
  delay(10);
  value = analogRead(water_sensor);
  percent = value / maxVal * 100;
  digitalWrite(power, LOW);

  // Print on console
//  Serial.print("Sensor value: ");
//  Serial.print(value);
//  Serial.println();

  // Read button/set states
  previousState = currentState;
  buttonState = digitalRead(button);
//  Serial.print("Button state:");
//  Serial.print(buttonState);
//  Serial.print(" Page number:");
//  Serial.print(page);
//  Serial.println();
  currentState = buttonState;
  if (currentState == 1 && previousState == 0) {
    page++;
    if (page > 3) {
      page = 0;
    }
  }
  
  // Calculate time remaining
//  if (millis() - timestamp > interval) {
//    timestamp = millis();
//    waterRemaining = millis();
//    digitalWrite(relayModule, LOW);
//  }
//  if (waterRemaining + waterTime > millis()) {
//    digitalWrite(relayModule, HIGH);
//  }
//  timeRemaining = interval - (millis() - timestamp);
  timeRemaining = interval - (millis() - timestamp);
  if (timeRemaining < 0) {
    timestamp = millis();
    waterTimestamp = millis();
  }
  waterRemaining = waterTime - (millis() - waterTimestamp);
  if (waterRemaining > 0) {
    digitalWrite(relayModule, LOW);
  } else {
    digitalWrite(relayModule, HIGH);
  }

  Serial.print("Time remaining: ");
  Serial.print(timeRemaining);
  Serial.print(" Water Time remaining: ");
  Serial.print(waterRemaining);
  Serial.println();

  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  if (page == 0) {
    // Moisture Level
    lcd.print("Moisture Level:");

    lcd.setCursor(0, 1);
    lcd.print(percent);

    lcd.setCursor(4, 1);
    lcd.print("%");
  } else if (page == 1) {
    // Time interval between watering 
    lcd.print("Break interval:");

    lcd.setCursor(0, 1);
    lcd.print(interval / 1000 / 60);
    lcd.setCursor(5, 1);
    lcd.print("minutes");
  } else if (page == 2) {
    // Time interval during watering
    lcd.print("Water interval:");

    lcd.setCursor(0, 1);
    lcd.print(waterTime / 1000);
    lcd.setCursor(3, 1);
    lcd.print("seconds");
  
  } else if(page == 3) {
    // Time until next water
    lcd.print("Next watering:");

    lcd.setCursor(0, 1);
    lcd.print(timeRemaining / 1000 / 60);

    lcd.setCursor(5, 1);
    lcd.print("minutes");
  }

  lcd.setCursor(15, 1);
  lcd.print(page+1);

  delay(100);
//counter++;
//  if (counter > 3) {
//    page++;
//    if (page > 3) {
//      page = 0;
//    }
//    counter = 0;
//  }
}

