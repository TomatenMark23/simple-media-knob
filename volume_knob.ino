/*  Hardware used:
    Board: 
      Arduino Pro Micro

    Rotary Encoder: 
      KY-040
      
    pin layout:
     KY-040 - Arduino
        CLK - Pin 2
        DT  - Pin 3
        SW  - Pin 4
        +   - VCC
        GND - GND
*/

#include <HID-Project.h>

const int pinCLK = 2;
const int pinDT  = 3;
const int pinSW  = 4;

int lastCLKState;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
const unsigned long doubleClickGap = 350;
const unsigned long holdTime       = 600;

int pressCount = 0;
bool buttonState = HIGH;
bool lastButtonState = HIGH;
bool isHolding = false;
unsigned long buttonDownTime = 0;
unsigned long lastReleaseTime = 0;

void setup() {
  pinMode(pinCLK, INPUT_PULLUP);
  pinMode(pinDT,  INPUT_PULLUP);
  pinMode(pinSW,  INPUT_PULLUP);

  lastCLKState = digitalRead(pinCLK);

  // Initialize both interfaces so Linux registers the full HID device
  BootKeyboard.begin();
  Consumer.begin();
}

void loop() {
  handleEncoder();
  handleButton();
}

void handleEncoder() {
  int currentCLKState = digitalRead(pinCLK);

  if (currentCLKState != lastCLKState && currentCLKState == LOW) {
    if (digitalRead(pinDT) != currentCLKState) {
      Consumer.write(MEDIA_VOLUME_UP);
    } else {
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
  }
  lastCLKState = currentCLKState;
}

void handleButton() {
  bool reading = digitalRead(pinSW);
  unsigned long now = millis();

  if (reading != lastButtonState) {
    lastDebounceTime = now;
  }

  if ((now - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && buttonState == HIGH) {
      buttonState = LOW;
      buttonDownTime = now;
      isHolding = false;
    }
    else if (reading == HIGH && buttonState == LOW) {
      buttonState = HIGH;
      if (!isHolding) {
        pressCount++;
        lastReleaseTime = now;
      }
    }
  }

  if (buttonState == LOW && !isHolding && (now - buttonDownTime >= holdTime)) {
    isHolding = true;
    pressCount = 0; 
    Consumer.write(MEDIA_VOLUME_MUTE);
  }

  if (pressCount > 0 && (now - lastReleaseTime > doubleClickGap) && buttonState == HIGH) {
    if (pressCount == 1) {
      Consumer.write(MEDIA_PLAY_PAUSE);
    } else if (pressCount == 2) {
      Consumer.write(MEDIA_NEXT);
    } else if (pressCount >= 3) {
      Consumer.write(MEDIA_PREV);
    }
    pressCount = 0;
  }

  lastButtonState = reading;
}