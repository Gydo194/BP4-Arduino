#define POTMETER_PIN A3

#define LED_0 4
#define LED_1 5
#define LED_2 6
#define LED_3 7
#define LED_4 8
#define LED_5 9
#define LED_6 10

// verbind AREF met 5v om een geeijkte uitlezing te verkrijgen


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(500);

  pinMode(POTMETER_PIN, INPUT);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
}

long get_percentage() {
  const int reading = analogRead(POTMETER_PIN);
  Serial.print(F("READING:"));
  Serial.println(reading);
  return map((long) reading, 0, 1023, 0, 7);
}

void set_leds(const uint8_t num) {
  digitalWrite(LED_0, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_5, LOW);
  digitalWrite(LED_6, LOW);

  // switchcase fall-through
  switch(num) {
    case 7:
      digitalWrite(LED_6, HIGH);
    case 6:
      digitalWrite(LED_5, HIGH);
    case 5:
      digitalWrite(LED_4, HIGH);
    case 4:
      digitalWrite(LED_3, HIGH);
    case 3:
      digitalWrite(LED_2, HIGH);
    case 2:
      digitalWrite(LED_1, HIGH);
    case 1:
      digitalWrite(LED_0, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  long mapped = get_percentage();
  Serial.print(F("MAPPED:"));
  Serial.println(mapped);

  set_leds((uint8_t) mapped);
}
