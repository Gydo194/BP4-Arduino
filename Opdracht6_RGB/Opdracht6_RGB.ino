#define PIN_R 11
#define PIN_G 10
#define PIN_B 9

#define FRAME_TIME_MS 50

void setup()
{
  Serial.begin(9600);
  delay(500);

  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);

  uint32_t mask = 0;

  for(;;) {
    do_frame(&mask);
    delay(FRAME_TIME_MS);
  }
}

void do_frame(uint32_t * const mask) {
  // AND-out de respectieve waarden voor rood, groen en blauw
  uint8_t red   = (*mask & 0x00FF0000) >> 16;
  uint8_t green = (*mask & 0x0000FF00) >> 8;
  uint8_t blue  = (*mask & 0x000000FF) >> 0;
 mask hardware interrupts
  // set de pwm waarden
  analogWrite(PIN_R, red);
  analogWrite(PIN_G, green);
  analogWrite(PIN_B, blue);

  Serial.print(red, BIN);
  Serial.print(" ");
  Serial.print(green, BIN);
  Serial.print(" ");
  Serial.println(blue, BIN);
  
  // increment de teller
  (*mask)++;
  
  // reset naar 0 wanneer de range doorlopen is.
  // ivm we maar 24 bits nodig hebben voor RGB kan ik geen misbruik maken van de integer overflow
  if((*mask & 0xFF000000) > 0) {
    *mask = 0x00;
  }
}

void loop()
{
  // doe niks
}