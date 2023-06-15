/*
* Waveshare사의 Sensors Pack 구성품인 DHT11 Sensor의 ESP32 사용 예제입니다.
* 온습도 센서로 온도, 습도 등을 측정합니다.
* 참조 : https://playground.arduino.cc/Main/DHT11Lib/
* ※ 라이브러리 및 예제코드 라이센스 정보는 dht11.cpp 파일 상단 참조
*
* DHT11 Sensor를 아래와 같이 연결하거나 -PIN- 부분의 값을 연결 상태에 맞게 변경해 주시면 됩니다. 
*/
//-------PIN---------
#define DHT11PIN   26       // DOUT
// GND = GND
// VCC = 3.3V
//--------------------
#include "dht11.h"

dht11 DHT11;

double Fahrenheit(double celsius) 
{
    return 1.8 * celsius + 32;
}   

double Kelvin(double celsius)
{
    return celsius + 273.15;
}    

double dewPoint(double celsius, double humidity)
{
    double A0= 373.15/(273.15 + celsius);
    double SUM = -7.90298 * (A0-1);
    SUM += 5.02808 * log10(A0);
    SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
    SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
    SUM += log10(1013.246);
    double VP = pow(10, SUM-3) * humidity;
    double T = log(VP/0.61078);   // temp var
    return (241.88 * T) / (17.558-T);
}

double dewPointFast(double celsius, double humidity)
{
    double a = 17.271;
    double b = 237.7;
    double temp = (a * celsius) / (b + celsius) + log(humidity/100);
    double Td = (b * temp) / (a - temp);
    return Td;
}


void setup()
{
    Serial.begin(115200);
    Serial.println("DHT11 TEST PROGRAM ");
    Serial.print("LIBRARY VERSION: ");
    Serial.println(DHT11LIB_VERSION);
    Serial.println();
}

void loop()
{
    Serial.println("\n");

    int chk = DHT11.read(DHT11PIN);

    Serial.print("Read sensor: ");
    switch (chk)
    {
    case DHTLIB_OK: 
        Serial.println("OK"); 
        break;
    case DHTLIB_ERROR_CHECKSUM: 
        Serial.println("Checksum error"); 
        break;
    case DHTLIB_ERROR_TIMEOUT: 
        Serial.println("Time out error"); 
        break;
    default: 
        Serial.println("Unknown error"); 
        break;
    }

    Serial.print("Humidity (%): ");
    Serial.println((float)DHT11.humidity, 2);

    Serial.print("Temperature (oC): ");
    Serial.println((float)DHT11.temperature, 2);

    Serial.print("Temperature (oF): ");
    Serial.println(Fahrenheit(DHT11.temperature), 2);

    Serial.print("Temperature (K): ");
    Serial.println(Kelvin(DHT11.temperature), 2);

    Serial.print("Dew Point (oC): ");
    Serial.println(dewPoint(DHT11.temperature, DHT11.humidity));

    Serial.print("Dew PointFast (oC): ");
    Serial.println(dewPointFast(DHT11.temperature, DHT11.humidity));

    delay(2000);
}
