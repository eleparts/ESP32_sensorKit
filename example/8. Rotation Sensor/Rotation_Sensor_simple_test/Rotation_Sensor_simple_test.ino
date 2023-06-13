/* 
* Waveshare사의 Sensors Pack 구성품인 Rotation Sensor의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* 간단 테스트로 각 동작 별 입력 변화를 확인하는 동작을 합니다.
* ※ Rotation Sensor는 회전 시 A와 B가 방향에 따라 순서대로 스위칭 됩니다.
* 이를 이용해 회전 방향을 특정할 수 있습니다.
* 
* Rotation Sensor를 아래와 같이 연결하거나 -PIN- 부분의 값을 연결 상태에 맞게 변경해 주시면 됩니다. 
*/
//-------PIN---------
#define PINA 18 
#define PINB 17 
#define PINSW 22 
// GND = GND
// VCC = 3.3V
//--------------------

int a,b,sw =0;

void setup()
{
  Serial.begin(115200);

  pinMode(PINA,INPUT); 
  pinMode(PINB,INPUT);
  pinMode(PINSW,INPUT); 
}

void loop()
{ 
  a = digitalRead(PINA);
  b = digitalRead(PINB);
  sw = digitalRead(PINSW);

  Serial.printf("value = %d, \t%d, \t%d \n",a,b,sw);

  delay(1);
  
}
