
/*
  Colorimetric PCR Board Firmware (Simplified)
  Author: 박인근
*/

#define BLOCK_TEMP_PIN A0
#define LID_TEMP_PIN   A1
#define BLOCK_HEATER_PIN 5
#define LID_HEATER_PIN   6

double blockTarget = 95.0;
double lidTarget = 105.0;
double blockCurrent = 0.0;
double lidCurrent = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(BLOCK_HEATER_PIN, OUTPUT);
  pinMode(LID_HEATER_PIN, OUTPUT);
}

void loop() {
  blockCurrent = readTemperature(BLOCK_TEMP_PIN);
  lidCurrent = readTemperature(LID_TEMP_PIN);

  double blockOutput = computePID(blockCurrent, blockTarget);
  double lidOutput = computePID(lidCurrent, lidTarget);

  analogWrite(BLOCK_HEATER_PIN, (int)blockOutput);
  analogWrite(LID_HEATER_PIN, (int)lidOutput);

  Serial.print("Block: ");
  Serial.print(blockCurrent);
  Serial.print(" Lid: ");
  Serial.println(lidCurrent);

  delay(500);
}

double readTemperature(int pin) {
  int adc = analogRead(pin);
  double voltage = adc * (5.0 / 1023.0);
  return (voltage - 0.5) * 100; // Dummy conversion
}

double computePID(double current, double target) {
  double error = target - current;
  double output = 2.0 * error; // Very simple P-controller for demo
  output = constrain(output, 0, 255);
  return output;
}

/* 
  실제 코드에선 2중 PID 정밀 제어 관련 코드로 작성되었습니다.

  PID Auto tune (오토튜닝 기반 파라미터 조정 기능)
  
  실제 PID 관련 변수들은 ROM에 저장됩니다.

  자동 팬 제어 및 온도 상승률 감시

*/