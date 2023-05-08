#define LED_RED_PIN   11
#define LED_GREEN_PIN 12

#define DELAY_PERIOD_MS 1000

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  Serial.begin(9600);
  delay(1000);
}



#define STATE_RED   0
#define STATE_GREEN 1

static uint8_t state = STATE_RED;

void loop() {
  // put your main code here, to run repeatedly:
  switch(state) {
    case STATE_GREEN:
      Serial.println("RED -> GREEN");
      analogWrite(LED_RED_PIN, 255);
      analogWrite(LED_GREEN_PIN, 0);
      state = STATE_RED;
      delay(DELAY_PERIOD_MS);
      break;

    case STATE_RED:
    default:
    Serial.println("GREEN -> RED");
      analogWrite(LED_RED_PIN, 0);
      analogWrite(LED_GREEN_PIN, 255);
      state = STATE_GREEN;
      delay(DELAY_PERIOD_MS);
      break;
  }
}
