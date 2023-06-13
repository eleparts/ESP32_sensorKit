/* 
* Waveshare사의 Sensors Pack 구성품인 Moisture(Liquid Level) Sensor의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* 수분을 감지하여 전압이 변화합니다. 토양 수분량을 감지할 수 있습니다.
* 
* Moisture Sensor를 아래와 같이 연결하거나 -PIN- 부분의 값을 연결 상태에 맞게 변경해 주시면 됩니다. 
*/
//-------PIN---------
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
  pinMode(AOUT, INPUT);
}

void loop()
{
  
  ad_value = analogRead(AOUT);
  
  // ADC 출력 값 확인용
  //Serial.println(ad_value);
  
  // 감지 민감도 변경 - 위의 ADC 값을 주석 해제하여 측정 후 적절히 변경해주면 됩니다.
  if (ad_value > 800)
  {
    // 축축함 - 수분 감지됨
    Serial.print("Wet!! (ADC = ");
    Serial.print(ad_value * 3.3 / resolution_value);
    Serial.println("V)");
  } 
  else
  {
    // 건조함 - 수분 감지되지 않음
    Serial.print("Dry (ADC = ");
    Serial.print(ad_value * 3.3 / resolution_value);
    Serial.println("V)");
  }
  
  delay(500);
}