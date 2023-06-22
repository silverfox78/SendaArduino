#include <Wire.h>
#include <RTClib.h>

#define BAUD_RATE 9600
#define DELAYTIME 1000

RTC_DS1307 RTC;
bool RTC_working = false;

void setup() {
  Serial.begin(BAUD_RATE);
  Wire.begin();
  if (!RTC.begin()) {
    Serial.println("No hay RTC.");
    RTC_working = false;  
  }
  else {
    Serial.println("RTC correcto. Iniciando captura de datos");
    RTC.adjust(DateTime(__DATE__, __TIME__));
    RTC_working = true; 
  }
}

void loop() {
  if (RTC_working) {
    static DateTime now; 
    now = RTC.now();

    Serial.print(now.hour());
    Serial.print(":");
    Serial.println(now.minute());

    delay(DELAYTIME);
  } else {
    Serial.println("Error: No hay RTC.");
    delay(DELAYTIME);
  }
}
