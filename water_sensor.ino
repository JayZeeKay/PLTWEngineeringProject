#define water_sensor A0
#define power 7
#define led 3

int value = 0;
int brightness = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(water_sensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(power, OUTPUT);
  digitalWrite(power, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(power, HIGH);
  delay(10);
  value = analogRead(water_sensor);
  digitalWrite(power, LOW);

  brightness = value * 2 * 256 / 180;
  analogWrite(led, brightness);
  
  Serial.print("Sensor value: ");
  Serial.print(value);
  Serial.print("  LED output: ");
  Serial.print(brightness);
  Serial.println();
  
  delay(1000);
}
