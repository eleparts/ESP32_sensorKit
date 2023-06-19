/* 
* Waveshare사의 Sensors Pack 구성품인 TCS3200 Color Sensor의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* 컬러 센서는 센서 내부에 R,G,B 색상에 해당하는 필터가 있는 포토 다이오드가 있어 각 색상별로 반사되는 빛의 세기(광도)를 측정합니다. 
*
* 본 예제는 1.TCS3200_Calibration에서 측정한 데이터를 입력한 뒤 어느 빛의 세기가 가장 큰지 비교, 컬러 센서의 어느 색이 가장 Red/Green/Blue에 가까운지 판단합니다.
* ※ 본 컬러 센서는 각각 R/G/B 색의 필터가 있는 포토 다이오드를 통해 각 색상 파장의 세기 광도를 측정합니다.
* ※ 따라서, 같은 색이라도 표면의 빛 반사량, 주변 밝기 등에 따라 값이 달라질 수 있습니다. 
* >> 0% = 빛 반사가 적음 = 검정에 가까움 / 100% = 빛이 전부 반사됨 = 흰색에 가까움
* 
* TCS3200 Color Sensor를 아래와 같이 연결하거나 -PIN- 부분의 값을 연결 상태에 맞게 수정해 줍니다. 
*/
//-------PIN---------0
#define LED  27   // 항시 ON = VCC 
#define OUT  26
#define S3   18
#define S2   5
#define S1   17
#define S0   16
// GND = GND
// VCC = 3.3V
//--------------------

//----------- RGB Calibration data -----------
// 1.TCS3200_Calibration 에서 측정된 값을 넣어 줍니다. ( MIN = White, MAX = Black 측정 값)
// min/max : R=[RED_MIN]/[RED_MAX] G=[GREEN_MIN]/[GREEN_MAX] B=[BLUE_MIN]/[BLUE_MAX]
#define RED_MIN     1
#define RED_MAX     999

#define GREEN_MIN   1
#define GREEN_MAX   999

#define BLUE_MIN    1
#define BLUE_MAX    999
//--------------------------------------------

// 검정색 최대 반사율, 흰색 최소 반사율 (검정/흰색 구분이 잘 안되는 경우 적당히 조정해 줍니다)
#define BLACK_ALBEDO  45   // 낮을수록 검은색, 0% 반사 (빛을 흡수)
#define WHITE_ALBEDO  80   // 높을수록 흰색, 100% 반사

int rgb_freq[3] = {0,};
/* 센서 내부에는 각 색상(R/G/B/No필터)의 필터가 있는 LED가 있으며, S2/S3로 선택해 데이터를 수신
* rgb_freq[0] = Red     : S2 / S3 : LOW  / LOW 
* rgb_freq[1] = Green   : S2 / S3 : HIGH / HIGH
* rgb_freq[2] = Blue    : S2 / S3 : LOW  / HIGH
* X             Cleare  : S2 / S3 : HIGH / LOW 
*/

int red_value = 0, green_value = 0, blue_value = 0;

void selectPhotodiode(int S2_sw, int S3_sw)
{
  digitalWrite(S2, S2_sw);
  digitalWrite(S3, S3_sw);
}

void setup() 
{
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(OUT, INPUT);

  // S0, S1 핀 설정 (주파수 스케일 20% / 120kHz)
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // LED ON
  digitalWrite(LED, HIGH);
}

void loop() 
{
  // Red
  selectPhotodiode(LOW, LOW);
  rgb_freq[0] = pulseIn(OUT, LOW);
  red_value = map(rgb_freq[0], RED_MIN, RED_MAX, 100, 0);   // 각 색상별 광도 측정 범위를 0~100으로 재 조정해 줍니다.

  // Green
  selectPhotodiode(HIGH, HIGH);
  rgb_freq[1] = pulseIn(OUT, LOW);
  green_value = map(rgb_freq[1], GREEN_MIN, GREEN_MAX, 100, 0);
  
  // Blue
  selectPhotodiode(LOW, HIGH);
  rgb_freq[2] = pulseIn(OUT, LOW);
  blue_value = map(rgb_freq[2], BLUE_MIN, BLUE_MAX, 100, 0);

  Serial.print((String)"Red = " + red_value + "% \t Green = " +  green_value + "% \t Blue = " + blue_value + "% \t\t");


  // 검정, 흰색, 빨강, 녹색, 파랑 구분하는 부분
  if(red_value < BLACK_ALBEDO && green_value < BLACK_ALBEDO && blue_value < BLACK_ALBEDO)
  {
    Serial.println("-> Black!!!");

  }else if(red_value > WHITE_ALBEDO && green_value > WHITE_ALBEDO && blue_value > WHITE_ALBEDO)
  {
    Serial.println("-> White!!!");

  }else
  {
    if((red_value > green_value) && (red_value > blue_value))    // RED
    {
      Serial.println("-> Red!!!");

    }else if((green_value > red_value) && (green_value > blue_value))  // GREEN
    {
      Serial.println("-> Green!!!");

    }else if((blue_value > red_value) && (blue_value > green_value))  // Blue
    {
      Serial.println("-> Blue!!!");

    }else
    {
      Serial.println("-> Impossible to verify");
    }
  }

  delay(500);

}
