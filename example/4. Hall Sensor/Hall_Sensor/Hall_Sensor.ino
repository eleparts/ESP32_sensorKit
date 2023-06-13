/* 
* Waveshare사의 Sensors Pack 구성품인 Hall Sensor의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* 자석(자기장)을 감지할 수 있습니다.
* ※ 자석의 방향에 따라 디지털 출력은 감지값을 출력하지 않을 수 있습니다, ADC 출력값을 참고하시면 자석 방향 확인이 가능합니다.
*
* Hall Sensor를 아래와 같이 연결하거나 -PIN- 부분의 값을 연결 상태에 맞게 변경해 주시면 됩니다. 
*/
//-------PIN---------
#define DOUT   26
#define AOUT   27     // ADC 지원 핀 사용
// GND = GND
// VCC = 3.3V
//--------------------

// 분해능 설정 12bit : 4096 (0~4095)
#define ADC_RESOLUTION_BIT    12
#define ADC_RESOLUTION_VALUE  4096 

int ad_value;
int resolution_value = ADC_RESOLUTION_VALUE - 1;

void setup()
{ 
  Serial.begin(115200);
  analogReadResolution(ADC_RESOLUTION_BIT);
  pinMode(DOUT, INPUT);
  pinMode(AOUT, INPUT);
}

void loop(){
  
  ad_value = analogRead(AOUT);
  
  if (digitalRead(DOUT) == LOW)
  { 
    // 자석 감지
    Serial.print("The Magnet is near!!! (ADC = ");
    Serial.print(ad_value * 3.3 / resolution_value);
    Serial.println("V)");
  } 
  else
  {
    // 감지되지 않음
    Serial.print("The Magnet is far!!! (ADC = ");
    Serial.print(ad_value * 3.3 / resolution_value);
    Serial.println("V)");
  }
  
  delay(500);
}
