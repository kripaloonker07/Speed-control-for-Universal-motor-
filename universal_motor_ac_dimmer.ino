
#define triacPin 3
#define switchPin1 5
#define switchPin2 6
#define switchPin3 7
#define switchPin4 8
#define zeroCrossPin 2

const unsigned long quarterCycleDelay40Hz = 4000;  
const unsigned long quarterCycleDelay50Hz = 5000;
const unsigned long quarterCycleDelay30Hz = 3000;
const unsigned long quarterCycleDelay60Hz = 6000;
volatile unsigned long currentMicro = 0;
volatile bool zeroCrossDetected = false;

const unsigned long onTime1 = 1000;   
const unsigned long onTime2 = 3000; 
const unsigned long offTime = 1000;    
const unsigned long onTime3 = 10000;  
const unsigned long onTime4 = 4000;  

void setup() {
  pinMode(triacPin, OUTPUT);
  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);
  pinMode(switchPin3, INPUT_PULLUP);
  pinMode(switchPin4, INPUT_PULLUP);
  pinMode(zeroCrossPin, INPUT_PULLUP);
  digitalWrite(triacPin, LOW);
  attachInterrupt(digitalPinToInterrupt(zeroCrossPin), zeroCrossInterrupt, RISING);
}

void loop() {
  static int switchState1 = 1;
  static int switchState2 = 1;
  static int switchState3 = 1;
  static int switchState4 = 1;
  static unsigned long lastSwitchCheck = 0;

  if (millis() - lastSwitchCheck >= 1000) {
    switchState1 = digitalRead(switchPin1);
    switchState2 = digitalRead(switchPin2);
    switchState3 = digitalRead(switchPin3);
    switchState4 = digitalRead(switchPin4);
    lastSwitchCheck = millis();
  }

  // Control for Switch 1
  if (switchState1 == 0 && zeroCrossDetected) {
    zeroCrossDetected = false;

    for (int cycle = 0; cycle < 2; cycle++) { 
      unsigned long startTime = millis();
      unsigned long elapsedTime = 0;
      while (elapsedTime < onTime1) {
        digitalWrite(triacPin, LOW);
        if (micros() - currentMicro >= quarterCycleDelay40Hz) {
          digitalWrite(triacPin, HIGH);
          delayMicroseconds(1000);
          digitalWrite(triacPin, LOW);
        }
        elapsedTime = millis() - startTime;
      }
      delay(offTime);
    }
  }
  // Control for Switch 2
  if (switchState2 == 0 && zeroCrossDetected) {
    zeroCrossDetected = false;

    for (int cycle = 0; cycle < 2; cycle++) { 
      unsigned long startTime = millis();
      unsigned long elapsedTime = 0;
      
      while (elapsedTime < onTime2) {
        digitalWrite(triacPin, LOW);
        if (micros() - currentMicro >= quarterCycleDelay50Hz) { 
          digitalWrite(triacPin, HIGH);
          delayMicroseconds(1000);
          digitalWrite(triacPin, LOW);
        }
        elapsedTime = millis() - startTime;
      }
      delay(2000);
    }
  }
  if (switchState3 == 0 && zeroCrossDetected) {
    zeroCrossDetected = false;

    for (int cycle = 0; cycle < 2; cycle++)  
     {
      unsigned long startTime = millis();
      unsigned long elapsedTime = 0;

      
      while (elapsedTime < onTime3) {
        digitalWrite(triacPin, LOW);
        if (micros() - currentMicro >= quarterCycleDelay30Hz) {
          digitalWrite(triacPin, HIGH);
          delayMicroseconds(1000);
          digitalWrite(triacPin, LOW);
        }
        elapsedTime = millis() - startTime;
      }
      delay(offTime);
    }
  }
  if (switchState4 == 0 && zeroCrossDetected) {
    zeroCrossDetected = false;

    for (int cycle = 0; cycle < 2; cycle++) 
     { 
      unsigned long startTime = millis();
      unsigned long elapsedTime = 0;

      
      while (elapsedTime < onTime4) {
        digitalWrite(triacPin, LOW);
        if (micros() - currentMicro >= quarterCycleDelay60Hz) {
          digitalWrite(triacPin, HIGH);
          delayMicroseconds(1000);
          digitalWrite(triacPin, LOW);
        }
        elapsedTime = millis() - startTime;
      }
      delay(offTime);
    }                                                                                                                                                               
  }
  if (switchState1 == 1 && switchState2 == 1 && switchState3 == 1 && switchState4 == 1) 
  {
    digitalWrite(triacPin, LOW);
  }
}
void zeroCrossInterrupt() {
  zeroCrossDetected = true;
  currentMicro = micros();
}
