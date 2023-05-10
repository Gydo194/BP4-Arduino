#define SENSOR_PIN A3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);

  pinMode(SENSOR_PIN, INPUT);
}

double read_sensor() {
  const long reading = analogRead(SENSOR_PIN);
  return (double) map(reading, 0, 1023, 0, 5000) / (double) 10;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(read_sensor());
}
