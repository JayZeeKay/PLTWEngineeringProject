int relayModule = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(relayModule, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relayModule, HIGH);
  delay(1000);
  digitalWrite(relayModule, LOW);
  delay(1000);
}
