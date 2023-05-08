// State defenities
#define STATE_LEFT  0
#define STATE_RIGHT 1

#define DELAY_MS 500 //wachttijd

/* map index nummers naar io pins */
#define PIN_0  5
#define PIN_1  6
#define PIN_2  7
#define PIN_3  8
#define PIN_4  9
#define PIN_5  10
#define PIN_6  11
#define PIN_7  12

void setup() {
  // setup de IO direction
  pinMode(PIN_0, OUTPUT);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
  pinMode(PIN_5, OUTPUT);
  pinMode(PIN_6, OUTPUT);
  pinMode(PIN_7, OUTPUT);

  Serial.begin(9600);
  delay(500); // wacht op de serial port

  // state informatie
  static uint8_t mask  = 0x80; //1000 0000
  static uint8_t state = STATE_RIGHT;

  write_to_port(mask); //initialiseer LEDs
  delay(DELAY_MS); // startconditie LEDs

  // hoofd loop. zit hier ivm pointers naar variablen op de stack
  for(;;) {
    run_frame(&mask, &state);
  }
}

// zet de LEDs aan of uit aan de hand van bits in de mask
void write_to_port(const uint8_t mask) {
  digitalWrite(PIN_0,   (mask & 0x01) > 0 ? HIGH : LOW);
  digitalWrite(PIN_1,   (mask & 0x02) > 0 ? HIGH : LOW);
  digitalWrite(PIN_2,   (mask & 0x04) > 0 ? HIGH : LOW);
  digitalWrite(PIN_3,   (mask & 0x08) > 0 ? HIGH : LOW);
  digitalWrite(PIN_4,   (mask & 0x10) > 0 ? HIGH : LOW);
  digitalWrite(PIN_5,   (mask & 0x20) > 0 ? HIGH : LOW);
  digitalWrite(PIN_6,   (mask & 0x40) > 0 ? HIGH : LOW);
  digitalWrite(PIN_7,   (mask & 0x80) > 0 ? HIGH : LOW);
}

void run_frame(uint8_t * const mask, uint8_t * const state) {
  Serial.print("run_frame MASK= ");
  Serial.println(*mask, BIN);

  // state machine: bekijk in welke state we ons bevinden en beslis aan de hand daarvan wat te doen
  switch(*state) {
    // we gaan naar links
    case STATE_LEFT:
      run_frame_left(mask, state);
      break;

    // we gaan naar rechts
    case STATE_RIGHT:
    default:
      run_frame_right(mask, state);
      break;
  }
}

/* ga 1 stap naar links */
void run_frame_left(uint8_t * const mask, uint8_t * const state) {
  Serial.print("LEFT ");
  Serial.println(*mask, BIN);

  // wanneer de meest linkse bit 1 is, transition naar de RIGHT state om de andere kant op te gaan
  if((*mask & 0x80) > 0) {
    Serial.println("Transition to RIGHT");
    *state = STATE_RIGHT;
    return;
  }

  *mask <<= 1; //schuif 1 bit naar links
  write_to_port(*mask);

  delay(DELAY_MS);
}

/* ga 1 stap naar rechts */
void run_frame_right(uint8_t * const mask, uint8_t * const state) {
  Serial.print("RIGHT ");
  Serial.println(*mask, BIN);

  // wanneer de meest rechtse bit 1 is, transition naar de LEFT state
  if((*mask & 0x01) > 0) {
    Serial.println("Transition to LEFT");
    *state = STATE_LEFT;
    return;
  }

  *mask >>= 1; //schuif 1 bit naar rechts
  write_to_port(*mask); //schrijf de bitmask naar IO Poort

  delay(DELAY_MS);
}

void loop() {
  // niet gebruikt
}
