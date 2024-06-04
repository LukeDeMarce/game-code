#include <Adafruit_CircuitPlayground.h>


const int buttonStartPin = 4;  
const int buttonStopPin = 5;   
const int switchPin = 7;       


bool gameActive = false;
int currentLed = 0;
unsigned long lastUpdate = 0;
const int updateInterval = 100; 

void setup() {
  CircuitPlayground.begin();  

  
  pinMode(buttonStartPin, INPUT_PULLUP);  
  pinMode(buttonStopPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);

  clearAllPixels(); 
}

void loop() {
  if (digitalRead(switchPin) == LOW) { 
    handleStartButton();
    handleGameActive();
    handleStopButton();
  } else {
    clearAllPixels(); 
  }
}

void handleStartButton() {
  if (digitalRead(buttonStartPin) == LOW && !gameActive) {
    gameActive = true;
    currentLed = 0;
  }
}

void handleGameActive() {
  if (gameActive && millis() - lastUpdate > updateInterval) {
    lastUpdate = millis();
    spinLEDs();
  }
}

void handleStopButton() {
  if (digitalRead(buttonStopPin) == LOW && gameActive) {
    gameActive = false;
    maintainLastLED(); 
  }
}

void spinLEDs() {
  clearAllPixels();
  CircuitPlayground.setPixelColor(currentLed, CircuitPlayground.colorWheel((currentLed * 25) % 255)); 
  currentLed = (currentLed + 1) % 10;
}

void maintainLastLED() {
  clearAllPixels();
  CircuitPlayground.setPixelColor(currentLed, CircuitPlayground.colorWheel((currentLed * 25) % 255));
}

void clearAllPixels() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 0); 
  }
}


