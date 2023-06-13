/* 
* Waveshare사의 Sensors Pack 구성품인 Laser Sensor의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* 레이저로 물체를 감지합니다. 일반적으로 0.8m ~ 최대 1.5m 정도의 거리의 물체를 감지할 수 있습니다.
* ※ 전원 연결 시 레이저가 켜지므로 눈에 비추지 않도록 주의하십시오.
* 
* Laser Sensor를 아래와 같이 연결하거나 -PIN- 부분의 값을 연결 상태에 맞게 변경해 주시면 됩니다. 
*/
//-------PIN---------
#define DOUT   26
// GND = GND
// VCC = 3.3V
//--------------------

void setup()
{ 
  Serial.begin(115200);
  pinMode(DOUT, INPUT);
}

void loop()
{
  
  
  if(digitalRead(DOUT) == LOW)
  {
    // 감지됨
    Serial.println("Obstacles!!!");
  } 
  else
  {
    // 감지된 물체 없음
    Serial.println("NO Obstacles!");
  }
  
  delay(500);
}