const byte marqueePin = 31;
const byte borderChannelPins[] = {35, 37, 39};
const byte borderChannelPinCount = 3;
const byte arrowChannelPins[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44};
const byte arrowChannelPinCount = 8;

const int marqueeDurationOn = 1250;
const int marqueeDurationOff = 750;
byte marqueeState = LOW;
unsigned long marqueeMillis = 0;

void marquee(unsigned long currentMillis) {
  if (marqueeState == LOW && currentMillis - marqueeMillis >= marqueeDurationOff) {
    marqueeMillis = currentMillis;
    marqueeState = HIGH;
    digitalWrite(marqueePin, HIGH);
    Serial.println("Marquee: On");
  } else if (marqueeState == HIGH && currentMillis - marqueeMillis >= marqueeDurationOn) {
    marqueeMillis = currentMillis;
    marqueeState = LOW;
    digitalWrite(marqueePin, LOW);
    Serial.println("Marquee: Off");
  }
}

void setup() {
  byte i = 0;

  Serial.begin(9600);

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
}
