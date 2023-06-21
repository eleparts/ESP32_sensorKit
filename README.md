# ESP32_sensorKit
  
[ESP32 Sensor Kit](https://www.eleparts.co.kr/EPXDPVYB)의 ESP32 호환 예제 코드입니다.  
  
13종의 센서를 [ESP32 모듈(개발보드)](https://www.eleparts.co.kr/goods/catalog?code=001700360007)에 연결 후 간단하게 작동시켜 볼 수 있습니다.  

## 본품 구성 키트  
  
[BOM 구성](https://www.eleparts.co.kr/bom/share?pj_seq=UP3ORZ196&hseq=BB8R8PD3)  
  
## 권장 ESP32 개발 보드 및 부속  
  
### 개발보드  

[ESP32-DevKitC V4 호환보드(Ver. WROOM-32D)](https://www.eleparts.co.kr/goods/view?no=12671127)  

[전원 & 프로그램 업로드용 USB 케이블](https://www.eleparts.co.kr/goods/catalog?&code=005100060013&node_id=343027&overseas=Y&sort=&_=1687221600766)

개발 보드의 핀에 점퍼를 직접 꽂아 사용하여도 가능하나, 아래 추가 구성을 이용해 브레드보드에 고정해 사용 가능합니다.  

### 추가 구성 - 브래드보드 및 변환 핀헤더  

[투명 브레드보드 [ELB-80T] x 2 EA](https://www.eleparts.co.kr/goods/view?no=12154)  
-> **2개**를 연결하면 중앙에 ESP32 보드를 꽂아 줄 수 있습니다.(DevKitC V4 규격 기준 중앙 전원라인 2줄 필요)  

[2.54mm 1*40P 도금 15mm 변환 핀헤더](https://www.eleparts.co.kr/goods/view?no=12534571)  
-> 니퍼등을 이용해 반으로 자른 뒤 브레드보드에 꽂으면 Female 점퍼를 꽂아 사용할 수 있습니다.  
(또는 점퍼 케이블(Female 타입)에 꽂아 male 로 변환 가능)  

![브레드보드 2EA 사용 샘플 이미지](https://raw.githubusercontent.com/eleparts/ESP32_sensorKit/main/image/sample_01.jpg)
  
## 센서 목록  

센서 키트의 구성품 목록입니다.  

|번호       | 센서                           | 기능                                |
|-----------|-------------------------------|-------------------------------------|
|1          |MQ-5 Gas Sensor                | 가스 센서 - LPG, 천연/석탄가스 감지   |
|2          |Color Sensor                   | 컬러 센서 - 색상 감지                 |
|3          |Flame Sensor	                | 불꽃 센서 - 화염/불꽃 감지            |
|4          |Hall Sensor                    | 홀 센서 - 자석/자기장 감지            |
|5          |Infrared Reflective Sensor	    | 적외선 반사 센서 - 근접 물체 감지     |
|6          |Laser Sensor	                | 레이저 센서 - 물체 감지               |
|7          |Moisture Sensor                | 토양 수분 센서 - 수분 감지            |
|8          |Rotation Sensor                | 회전 센서 - 회전& 회전 방향 감지      |
|9          |Sound Sensor	                | 사운드 센서 - 소리 감지               |
|10         |Temperature-Humidity Sensor	| 온습도 센서 - 온도/습도 측정          |
|11         |Tilt Sensor                    | 흔들림 센서 - 흔들림/기울임 감지      |
|12         |UV Sensor                      | 자외선 센서 - 자외선 감지             |
|13         |Liquid Level Sensor	        | 액체 레벨 센서 - 수위 감지            |
  
## ESP32-DevKitC V4 핀 맵

![ESP32-DevKitC V4 Pin map](https://raw.githubusercontent.com/eleparts/ESP32_sensorKit/main/image/esp32-devkitC-v4-pinout.png)