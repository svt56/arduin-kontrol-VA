#include "Wire.h"
#include "iarduino_RTC.h"
#include <iarduino_OLED_txt.h> 
#include <Adafruit_INA219.h>
iarduino_RTC time (RTC_DS1302,5,7,6);  // для модуля DS1302 - RST, CLK, DAT
iarduino_OLED_txt myOLED(0x3C);
extern uint8_t MediumFont[];  
extern uint8_t SmallFontRus[];
extern uint8_t MediumFontRus[];
Adafruit_INA219 ina219; 

void setup() {
  Serial.begin(9600);
  time.begin();
    if (! ina219.begin()) { 
      Serial.println("Failed to find INA219 chip"); 
      while (1) { delay(10); }
    }
  // 0  sec, 30 min, 18 hour, 2 date, january, 2022, wed
  //time.settime(45, 53, 17, 11, 2, 24, 7);
  myOLED.begin(); 
  myOLED.clrScr();
  ina219.setCalibration_32V_1A ();

}

void loop() {
  float current_mA = 0;
  float busvoltage = 0;
//Serial.println(time.gettime("d-m-Y, H:i:s, D"));
Serial.println(time.gettime("H:i:s"));
  // ток в нагрузке
  current_mA = ina219.getCurrent_mA();
  // напряжение между GND и VIN- (нагрузка)
  busvoltage = ina219.getBusVoltage_V();
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
    Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
myOLED.setFont(SmallFontRus);
myOLED.print("Секунд         ", OLED_L, 1);
myOLED.setFont(MediumFontRus);
myOLED.print(String(millis()/1000) + "        ", OLED_L, 3);
udatetime();
myOLED.setFont(SmallFontRus);
myOLED.print("Минут           ", OLED_L, 1);
myOLED.setFont(MediumFontRus);
myOLED.print(String(millis()/1000/60) + "        ", OLED_L, 3);
udatetime(); 
myOLED.setFont(SmallFontRus);
myOLED.print("Часов            ", OLED_L, 1);
myOLED.setFont(MediumFontRus);
myOLED.print(String(millis()/1000/60/60) + "        ", OLED_L, 3);
udatetime();
myOLED.setFont(SmallFontRus);
myOLED.print("Ток нагрузки", OLED_L, 1);
myOLED.setFont(MediumFontRus);
myOLED.print(String(current_mA) + " " + "мA  ", OLED_L, 3);
udatetime();
myOLED.setFont(SmallFontRus);
myOLED.print("Вольт питания", OLED_L, 1);
myOLED.setFont(MediumFontRus);
myOLED.print(String(busvoltage) + " " + "В  ", OLED_L, 3);
udatetime();

}
void udatetime() { 
myOLED.setFont(SmallFontRus);
myOLED.print("Текущее время", OLED_L, 5);
myOLED.setFont(MediumFontRus);
myOLED.print(time.gettime("H:i:s"), OLED_L, 7);
delay(1000);
}