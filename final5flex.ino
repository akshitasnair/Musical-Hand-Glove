// Five Flex Sensor Musical Test with hysteresis + averaging

const int flexPin1 = A0;
const int flexPin2 = A1;
const int flexPin3 = A2;
const int flexPin4 = A3;
const int flexPin5 = A4;
const int buzzerPin = 8;

// Notes for each finger
const int note1 = 262;   // C4
const int note2 = 294;   // D4
const int note3 = 330;   // E4
const int note4 = 349;   // F4
const int note5 = 392;   // G4

// Thresholds with hysteresis (upper = bent, lower = relaxed)
int flexUpper1 = 880, flexLower1 = 870;  // Thumb
int flexUpper2 = 790, flexLower2 = 780;  // Index
int flexUpper3 = 955, flexLower3 = 945;  // Middle
int flexUpper4 = 915, flexLower4 = 905;  // Ring
int flexUpper5 = 885, flexLower5 = 875;  // Pinky

// States
bool isBent1 = false, isBent2 = false, isBent3 = false, isBent4 = false, isBent5 = false;

// Helper: average multiple readings to reduce noise
int readAverage(int pin) {
  long sum = 0;
  const int samples = 10;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return sum / samples;
}

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  Serial.println("Five Flex Sensors - bend to play notes!");
}

void loop() {
  int flexVal1 = readAverage(flexPin1);
  int flexVal2 = readAverage(flexPin2);
  int flexVal3 = readAverage(flexPin3);
  int flexVal4 = readAverage(flexPin4);
  int flexVal5 = readAverage(flexPin5);

  Serial.print("A0: "); Serial.print(flexVal1);
  Serial.print("   A1: "); Serial.print(flexVal2);
  Serial.print("   A2: "); Serial.print(flexVal3);
  Serial.print("   A3: "); Serial.print(flexVal4);
  Serial.print("   A4: "); Serial.println(flexVal5);

  // Apply hysteresis
  if (!isBent1 && flexVal1 >= flexUpper1) isBent1 = true;
  else if (isBent1 && flexVal1 <= flexLower1) isBent1 = false;

  if (!isBent2 && flexVal2 >= flexUpper2) isBent2 = true;
  else if (isBent2 && flexVal2 <= flexLower2) isBent2 = false;

  if (!isBent3 && flexVal3 >= flexUpper3) isBent3 = true;
  else if (isBent3 && flexVal3 <= flexLower3) isBent3 = false;

  if (!isBent4 && flexVal4 >= flexUpper4) isBent4 = true;
  else if (isBent4 && flexVal4 <= flexLower4) isBent4 = false;

  if (!isBent5 && flexVal5 >= flexUpper5) isBent5 = true;
  else if (isBent5 && flexVal5 <= flexLower5) isBent5 = false;

  // Decide tone output (priority order)
  if (isBent1) {
    tone(buzzerPin, note1);
    Serial.println("Sensor A0 bent → playing note1");
  } else if (isBent2) {
    tone(buzzerPin, note2);
    Serial.println("Sensor A1 bent → playing note2");
  } else if (isBent3) {
    tone(buzzerPin, note3);
    Serial.println("Sensor A2 bent → playing note3");
  } else if (isBent4) {
    tone(buzzerPin, note4);
    Serial.println("Sensor A3 bent → playing note4");
  } else if (isBent5) {
    tone(buzzerPin, note5);
    Serial.println("Sensor A4 bent → playing note5");
  } else {
    noTone(buzzerPin);
    Serial.println("All sensors relaxed → silence");
  }

  delay(50);
}