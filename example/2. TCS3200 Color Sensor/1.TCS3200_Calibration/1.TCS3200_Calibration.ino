/* 
* Waveshare사의 Sensors Pack 구성품인 TCS3200 Color Sensor의 ESP32 사용 예제입니다.
* 제품 페이지 : https://www.eleparts.co.kr/EPXDPVYB
* 컬러 센서는 센서 내부에 R,G,B 색상에 해당하는 필터가 있는 포토 다이오드가 있어 각 색상별로 반사되는 빛의 세기(광도)를 측정합니다. 
*
* 본 예제는 색상 캘리브레이션 작업을 위해 각 센서의 색상별로 포토 다이오드가 측정하는 최소/최대값을 측정하는 동작을 합니다.
* 검정색과 하얀색 2개의 물체를 준비한 뒤 각각의 색상 위에서 앞뒤로 움직이며 4~5초 정도씩 측정해 줍니다. 
* 최종 min/max 데이터를 2.TCS3200_RGB_Detector예제 의 [RGB Calibration data] 내부 #define 컬러 MIN/MAX 부분에 넣어 주시면 됩니다.
* ※ 검정색 위에서 값이 가장 크게 나와야 하나, 일반적인 검정색 물체도 빛을 100% 흡수하지 않기 때문에(+주변광의 영향을 받아) 검정색 위에서도 값이 변할 수 있습니다. 
* ※※ 만약 검정색 측정 중 평균 측정 값보다 너무 큰 값이 측정/저장된 경우 ESP32를 리셋해 다시 측정해 주어야 합니다.
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

int rgb_min_max[3][2] = {0,};
int rgb_freq[3] = {0,};
/* 센서 내부에는 각 색상(R/G/B/No필터)의 필터가 있는 LED가 있으며, S2/S3로 선택해 데이터를 수신
* rgb_freq[0] = Red     : S2 / S3 : LOW  / LOW 
* rgb_freq[1] = Green   : S2 / S3 : HIGH / HIGH
* rgb_freq[2] = Blue    : S2 / S3 : LOW  / HIGH
* X             Cleare  : S2 / S3 : HIGH / LOW 
*/


void selectPhotodiode(int S2_sw, int S3_sw)
{
  digitalWrite(S2, S2_sw);
  digitalWrite(S3, S3_sw);
}

void calibrationData(int *rgb)
{
  for(int i=0; i<3; i++)
  {
    // min 값 최초 강제 변경
    if(rgb_min_max[i][0] < 1)
    {
      rgb_min_max[i][0] = rgb[i];
    }

    // min , max 값 설정
    if(rgb[i] > rgb_min_max[i][1])      // max 업데이트
    {
      rgb_min_max[i][1] = rgb[i];

    }else if(rgb[i] < rgb_min_max[i][0])  // min 업데이트
    {
      rgb_min_max[i][0] = rgb[i];
    }
  }
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

  // Green
  selectPhotodiode(HIGH, HIGH);
  rgb_freq[1] = pulseIn(OUT, LOW);
  
  // Blue
  selectPhotodiode(LOW, HIGH);
  rgb_freq[2] = pulseIn(OUT, LOW);

  Serial.print((String)"Red = " + rgb_freq[0] + " \t Green = " +  rgb_freq[1] + " \t Blue = " + rgb_freq[2]);

  calibrationData(rgb_freq);

  Serial.println((String)"\t| min/max : R=" + rgb_min_max[0][0] +"/"+ rgb_min_max[0][1] + " G=" +  rgb_min_max[1][0] +"/"+ rgb_min_max[1][1] + " B=" + rgb_min_max[2][0] +"/"+ rgb_min_max[2][1]);

  delay(200);

}
