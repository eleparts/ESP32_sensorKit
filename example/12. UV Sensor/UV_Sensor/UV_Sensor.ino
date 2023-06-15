/* 
* Waveshare사의 Sensors Pack 구성품인 UV Sensor의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* UV(자외선)을 감지합니다. (인식 파장 200nm-370nm)
* 
* UV Sensor를 아래와 같이 연결하거나 -PIN- 부분의 값을 연결 상태에 맞게 변경해 주시면 됩니다. 
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

  if(ad_value>80)
  {
    Serial.print("UV up the standard \t | \t");
  }
  else
  {
    Serial.print("UV down the standard \t | \t");
  }
  // ADC data 출력 0~4095 (12bit 인 경우)
  Serial.print("ADC : "); 
  Serial.println(ad_value);

  delay(500);
}
