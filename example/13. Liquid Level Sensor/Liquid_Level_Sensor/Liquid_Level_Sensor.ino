/* 
* Waveshare사의 Sensors Pack 구성품인 Liquid Level Sensor의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* 모듈이 물에 잠기면 전압이 변화하기 때문에 대략적인 수위를 측정할 수 있습니다.
* 
* Liquid Level Sensor를 아래와 같이 연결하거나 -PIN- 부분의 값을 연결 상태에 맞게 변경해 주시면 됩니다. 
*/
//-------PIN---------
#define AOUT   27
// GND = GND
// VCC = 3.3V
//--------------------

// 분해능 설정 12bit : 4096 (0~4095)
#define ADC_RESOLUTION_BIT    12
#define ADC_RESOLUTION_VALUE  4096 

int ad_value = 0;

void setup()
{
  Serial.begin(115200);
  analogReadResolution(ADC_RESOLUTION_BIT);
  pinMode(AOUT, INPUT);
}

void loop()
{
  ad_value = analogRead(AOUT);

  // 모듈의 수위 측정에 따른 ADC 전압이 선형적이지 않으므로 적당히 조절 필요
  if(ad_value > 1024)
  {
    // 물에 잠겨 전압 증가 확인
    Serial.print("High water level\t| ");
  }
  else
  {
    // 물에 잠기지 않았거나 매우 적음
    Serial.print("Low water level \t| ");
  }

  Serial.print("ADC value: ");
  Serial.println(ad_value);

  delay(500);
}
