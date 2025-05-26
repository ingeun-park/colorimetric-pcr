
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

### 실제 상용 버전 (비공개)
- **2중 PID 제어**: Block/Lid 독립 제어
- **적응형 파라미터**: 구간별 차등 제어 로직
- **오버슈트 방지**: 출력 변화율 제한 + 적분 windup 방지
- **열간섭 보정**: 블럭 간 상호 영향 실시간 보상
- **오토튜닝**: Ziegler-Nichols 기반 자동 파라미터 조정

*상용 제품 특성상 핵심 알고리즘은 공개하지 않습니다*
