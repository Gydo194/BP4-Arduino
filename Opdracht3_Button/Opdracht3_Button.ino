#define BUTTON_PIN 2

#define EIMSK_INT0_MASK 0x01
#define EIFR_INT0_MASK  0x01

#define LED_PIN 11

#define LED_STATE_ON  1
#define LED_STATE_OFF 0

volatile bool pressed = false;

void button_falling_isr() {
  pressed = true;
}

void handle_press_event(uint8_t * const state) {
  switch(*state) {
    case LED_STATE_ON:
      transition_off(state);
    break;
    
    case LED_STATE_OFF:
    default:
      transition_on(state);
    break;
  }
}

void transition_off(uint8_t * const state) {
  analogWrite(LED_PIN, 0);
  *state = LED_STATE_OFF;
}

void transition_on(uint8_t * const state) {
  analogWrite(LED_PIN, 255);
  *state = LED_STATE_ON;
}

void setup() {

  Serial.begin(9600);
  delay(500);

  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_falling_isr, FALLING);


  uint8_t state = LED_STATE_OFF;

  for(;;) {
    if(pressed) {
      Serial.println("PRESSED");
      pressed = false; // reset de ISR flag

      handle_press_event(&state);

      EIMSK &= ~EIMSK_INT0_MASK; //mask externe interrupt op pin 2 tijdens de debounce periode. Zie ATmega328 datasheet pagina 55
      delay(50);
      EIFR &=  ~EIFR_INT0_MASK;  //clear de pending interrupt
      EIMSK |=  EIMSK_INT0_MASK;
    }
  }

}


void loop() {
  // doe niks
}