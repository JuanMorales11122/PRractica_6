#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C pantalla(0x27, 16, 2);
int bomba = 7;
int bz = 9;
RTC_DS3231 rtc;
const int pindatos = 3;
OneWire onewire(pindatos);
DallasTemperature sensor(&onewire);

void setup() {
  Serial.begin(9600);
  pinMode(bz,OUTPUT);
  sensor.begin();
  pinMode(bomba,OUTPUT);
  pantalla.init();
  pantalla.backlight();
  pantalla.clear();
if (! rtc.begin()) {		
 Serial.println("Modulo RTC no encontrado !");
 while (1);			
 }
 rtc.adjust(DateTime(__DATE__, __TIME__));	
}

void loop() {
DateTime fecha = rtc.now();	
sensor.requestTemperatures();
 Serial.print(fecha.day());		
 Serial.print("/");				
 Serial.print(fecha.month());		
 Serial.print("/");				
 Serial.print(fecha.year());		
 Serial.print(" ");				
 Serial.print(fecha.hour());
 Serial.print(":");	
 Serial.print(fecha.minute());
 Serial.print(":");	
 Serial.println(fecha.second()); 
 
 delay(1000);	


 if(fecha.minute() == 7){
   pantalla.clear();
  pantalla.setCursor(0, 0); // X, Y
  pantalla.print("Precaucion!");
  pantalla.setCursor(0, 1);
  pantalla.print("se regara agua");
  delay(1000);
  digitalWrite(bomba,LOW);
  pantalla.clear();
  pantalla.setCursor(0,0);
  pantalla.print(sensor.getTempCByIndex(0));
  tone(bz,650); 
  delay(10000);
  digitalWrite(bomba,HIGH);
  delay(40000);
 }
if(fecha.minute() < 7 ||fecha.minute() > 7){
  Serial.println("aun no es hora");
     pantalla.clear();
  pantalla.setCursor(0, 0); // X, Y
  pantalla.print("aun no es hora!");
  digitalWrite(bomba,HIGH);
}
 }		

