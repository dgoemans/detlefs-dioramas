#include <FastLED.h>

#define NUM_LEDS_1 20
#define NUM_LEDS_2 0

#define ON_COLOR_1 0xFFF2B3
#define ON_COLOR_2 0x284521

CRGB leds[NUM_LEDS_1  + NUM_LEDS_2];

#define COLOR 0
#define BUTTON_1_PIN 4
#define BUTTON_2_PIN 6
#define ONBOARD_LED_PIN 13

uint8_t button1State = LOW;
uint8_t button2State = LOW;


void setup() {
  Serial.begin(9600);

  pinMode(ONBOARD_LED_PIN,OUTPUT);
  pinMode(BUTTON_1_PIN,INPUT_PULLUP);
  pinMode(BUTTON_2_PIN,INPUT_PULLUP);

  FastLED.addLeds<NEOPIXEL, 2>(leds, NUM_LEDS_1 + NUM_LEDS_2);  

  button1State = digitalRead(BUTTON_1_PIN);

  if(button1State == HIGH) {
      for (int i = 0; i < NUM_LEDS_1; i++) {
        leds[i] = CRGB::Black; 
      }
    } else if(button1State == LOW) {
      for (int i = 0; i < NUM_LEDS_1; i++) {
        leds[i] = ON_COLOR_1; 
      }
    }

  button2State = digitalRead(BUTTON_2_PIN);
  if(button2State == HIGH) {
    for (int i = NUM_LEDS_1; i < NUM_LEDS_1+NUM_LEDS_2; i++) {
      leds[i] = CRGB::Black; 
    }
  } else if(button2State == LOW) {
    for (int i = NUM_LEDS_1; i < NUM_LEDS_1+NUM_LEDS_2; i++) {
      leds[i] = ON_COLOR_2; 
    }
  }
}

void loop() {
  uint8_t oldButton1State = button1State;
  button1State = digitalRead(BUTTON_1_PIN);

  if((oldButton1State == HIGH) != (button1State == HIGH)) {
    if(button1State == HIGH) {
      for (int i = 0; i < NUM_LEDS_1; i++) {
        leds[i] = CRGB::Black; 
      }
    } else if(button1State == LOW) {
      for (int i = 0; i < NUM_LEDS_1; i++) {
        leds[i] = ON_COLOR_1; 
      }
    }
  }

  uint8_t oldButton2State = button2State;
  button2State = digitalRead(BUTTON_2_PIN);

  if((oldButton2State == HIGH) != (button2State == HIGH)) {
    if(button2State == HIGH) {
      for (int i = NUM_LEDS_1; i < NUM_LEDS_1+NUM_LEDS_2; i++) {
        leds[i] = CRGB::Black; 
      }
    } else if(button2State == LOW) {
      for (int i = NUM_LEDS_1; i < NUM_LEDS_1+NUM_LEDS_2; i++) {
        leds[i] = ON_COLOR_2; 
      }
    }
  }

  FastLED.show();

  delay(500);
}