/* 
* Waveshare사의 Sensors Pack 구성품인 Sound Sensor의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* 소리를 감지할 수 있습니다.
* 
* Sound Sensor를 아래와 같이 연결하거나 -PIN- 부분의 값을 연결 상태에 맞게 수정해 줍니다. 
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
  pinMode(DOUT,INPUT);
  pinMode(AOUT,INPUT);
}

void loop()
{
  ad_value = analogRead(AOUT);

  if(digitalRead(DOUT) == LOW)
  {
    // 소리 감지
    Serial.print("Sound detected!!! (ADC = ");
    Serial.print(ad_value * 3.3 / resolution_value);
    Serial.println("V");
  }
  else
  { 
    // 소리 감지되지 않음
    Serial.print("Sound not detected (ADC = ");
    Serial.print(ad_value * 3.3 / resolution_value);
    Serial.println("V");
  }

  delay(500);
}
