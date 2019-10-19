const byte marqueePin = 31;
const byte borderChannelPins[] = {35, 37, 39};
const byte borderChannelPinCount = 3;
const byte arrowChannelPins[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44};
const byte arrowChannelPinCount = 12;

const int marqueeDurationOn = 1250;
const int marqueeDurationOff = 750;
byte marqueeState = 0;
unsigned long marqueeMillis = 0;

const int borderChaseInterval = 250;
byte borderChannelCurrent = 1;
unsigned long borderChaseMillis = 0;

const int arrowRestart = 2000;
const int arrowInterval = 100;
byte arrowState = 0;
byte arrowChannelCurrent = 1;
unsigned long arrowMillis = 0;

void marquee(unsigned long currentMillis) {
  if (marqueeState == 0 && currentMillis - marqueeMillis >= marqueeDurationOff) {
    marqueeMillis = currentMillis;
    marqueeState = 1;
    digitalWrite(marqueePin, HIGH);
  } else if (marqueeState == HIGH && currentMillis - marqueeMillis >= marqueeDurationOn) {
    marqueeMillis = currentMillis;
    marqueeState = 0;
    digitalWrite(marqueePin, LOW);
  }
}

void border(unsigned long currentMillis) {
  if (currentMillis - borderChaseMillis >= borderChaseInterval) {
    borderChaseMillis = currentMillis;
    digitalWrite(borderChannelPins[borderChannelCurrent - 1], LOW);
    if (borderChannelCurrent == borderChannelPinCount) {
      borderChannelCurrent = 1;
    } else {
      borderChannelCurrent++;
    }
    digitalWrite(borderChannelPins[borderChannelCurrent - 1], HIGH);
  }
}

void arrow(unsigned long currentMillis) {
  if (arrowState == 0 && currentMillis - arrowMillis >= arrowRestart) {
    arrowState = 1;
    arrowMillis = currentMillis;
    arrowChannelCurrent = 0;
    return;
  }
  if (arrowState == 1 && currentMillis - arrowMillis >= arrowInterval) {
    if (arrowChannelCurrent > arrowChannelPinCount) {
      return;
    }
    arrowMillis = currentMillis;
    if (arrowChannelCurrent > 0) {
      digitalWrite(arrowChannelPins[arrowChannelCurrent - 1], LOW);
    }
    arrowChannelCurrent++;
    if (arrowChannelCurrent <= arrowChannelPinCount) {
      digitalWrite(arrowChannelPins[arrowChannelCurrent - 1], HIGH);
    } else {
      arrowState = 0;
    }
  }
}

void setup() {
  byte i = 0;

  digitalWrite(marqueePin, LOW);
  pinMode(marqueePin, OUTPUT);

  for (i = 0; i < borderChannelPinCount; i++) {
    digitalWrite(borderChannelPins[i], LOW);
    pinMode(borderChannelPins[i], OUTPUT);
  }
  
  for (i = 0; i < arrowChannelPinCount; i++) {
    digitalWrite(arrowChannelPins[i], LOW);
    pinMode(arrowChannelPins[i], OUTPUT);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  marquee(currentMillis);
  border(currentMillis);
  arrow(currentMillis);
}
