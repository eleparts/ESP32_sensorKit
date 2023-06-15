/* 
* Waveshare사의 Sensors Pack 구성품인 Tilt Sensor의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* 기울기(흔들림)을 감지합니다. 내부의 구슬이 특정 방향으로 움직일 때 기울임이 감지됩니다.
* 
* Tilt Sensor를 아래와 같이 연결하거나 -PIN- 부분의 값을 연결 상태에 맞게 변경해 주시면 됩니다. 
*/
//-------PIN---------
#define DOUT   26
// GND = GND
// VCC = 3.3V
//--------------------

int cnt = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(DOUT, INPUT);
}

void loop()
{  
  if(digitalRead(DOUT) == HIGH)
  {
    // 흔들림 감지되지 않음
    if(cnt > 250)       // delay(2) * 250 (ms) 마다 '.' 출력 (= 0.5s)
    {
      Serial.print(".");
      cnt = 0;
    }
    cnt++;
  }
  else
  {
    // 흔들림이 감지됨
    Serial.println("\nShaking detected!!!");
    delay(1000);
  }

  delay(2);
}
