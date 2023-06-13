/* 
* Waveshare사의 Sensors Pack 구성품인 Rotation Sensor 의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* 인터럽트 기능을 이용해 방향을 체크, 방향에 따라 숫자를 증감시킵니다. 스위치를 누르면 숫자가 초기화됩니다.
* ※ Rotation Sensor는 회전 시 A와 B가 방향에 따라 순서대로 스위칭 됩니다.
* (A 방향 기준: 회전 시작 [A Low -> B Low -> A High -> B High] 회전 종료)이를 이용해 회전 방향을 특정할 수 있습니다. 
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

int dataA,dataB,dataC = 0;

int turn = 0;
bool interruptFlag = HIGH;
bool sensorFlag = HIGH;
bool swCnt = LOW;

void IRAM_ATTR InterruptA() 
{
  if(digitalRead(PINB) && interruptFlag)
  {
    sensorFlag = HIGH;    // 방향 설정
    interruptFlag = LOW;  // 인터럽트 연속/중복 실행 방지 + 실행 체크
    //Serial.println("Turn A");
  }
}

void IRAM_ATTR InterruptB() 
{
  if(digitalRead(PINA) && interruptFlag)
  {
    sensorFlag = LOW;
    interruptFlag = LOW;
    //Serial.println("Turn B");
  }
}

void IRAM_ATTR InterruptSW() 
{
  //Serial.println("PUSH");
  swCnt = HIGH;
}

void setup()
{
  Serial.begin(115200);

  pinMode(PINA,INPUT_PULLUP); 
  pinMode(PINB,INPUT_PULLUP);
  pinMode(PINSW,INPUT_PULLUP); 

  // 하강(FALLING)시 인터럽트 실행
  attachInterrupt(PINA, InterruptA, FALLING);
  attachInterrupt(PINB, InterruptB, FALLING);
  attachInterrupt(PINSW, InterruptSW, FALLING);
}


void loop()
{ 
  dataA = digitalRead(PINA);
  dataB = digitalRead(PINB);

  // 핀 A 및 B 가 둘 다 HIGH일때 실행(회전 동작이 종료되었을 때 진입)
  if(dataA&&dataB)
  { 
    // 인터럽트 실행 여부 체크
    if(!interruptFlag)
    {
      // sensorFlag : 회전 방향 체크해 숫자 cnt
      if(sensorFlag == HIGH)
      {
        Serial.println(--turn);
      
      }else if(sensorFlag == LOW)
      {
        Serial.println(++turn);
      }
      
      interruptFlag = HIGH;
    }
  }

  // 스위치가 눌린 경우 실행, 초기화
  if(swCnt)
  {
    turn = 0; 
    Serial.println("PUSH - CNT Reset");
    Serial.println(turn);
    swCnt = LOW;
  }

  delay(1);
}
