#include <Arduino.h>

#define HMC_CTRL  PA0
#define HMC_EN    PA1
#define BTN_PIN   PC13
#define LED_PIN   LED_BUILTIN

// Стани перемикача
enum RFSource {
  ANTENNA,    // вимірювання з антени
  REFERENCE   // еталон (термінатор 50 Ом)
};

RFSource currentSource = ANTENNA;

void setRFSource(RFSource source) {
  if (source == ANTENNA) {
    digitalWrite(HMC_EN, HIGH);
    digitalWrite(HMC_CTRL, LOW);
    Serial.println(">> Switched to: ANTENNA");
  } else {
    digitalWrite(HMC_EN, HIGH);
    digitalWrite(HMC_CTRL, HIGH);
    Serial.println(">> Switched to: REFERENCE (50 Ohm)");
  }
  currentSource = source;
}

void setup() {
  pinMode(HMC_CTRL, OUTPUT);
  pinMode(HMC_EN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);

  // Початковий стан — антена
  setRFSource(ANTENNA);
  Serial.println("HMC849 ready. Press button to switch.");
}

bool lastBtnState = HIGH;
uint32_t lastDebounce = 0;

void loop() {
  bool btnState = digitalRead(BTN_PIN);

  if (btnState != lastBtnState) {
    lastDebounce = millis();
    lastBtnState = btnState;
  }

  if ((millis() - lastDebounce) > 50) {
    if (btnState == LOW) {
      // Перемикаємо між антеною і еталоном
      if (currentSource == ANTENNA) {
        setRFSource(REFERENCE);
        digitalWrite(LED_PIN, HIGH); // LED горить = еталон
      } else {
        setRFSource(ANTENNA);
        digitalWrite(LED_PIN, LOW);  // LED згашений = антена
      }
      lastDebounce = millis();
    }
  }
}