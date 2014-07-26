#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <SoftwareSerial.h>

const int softwareTx = 8;
const int softwareRx = 7;
SoftwareSerial s7s(softwareRx, softwareTx);
char tempString[10];

const int buttonPin1 = 12;
const int buttonPin2 = 3;
int buttonState1 = 0;
int buttonState2 = 0;
const int analogInPin = A1;
int sensor = 0;
int val = 0;

const int ledPin =  13;

int LM35 = A0;
int LM352 = A2;
float SensorValue1 = 0;
float SensorValue2 = 0;
float temperatur = 0;
float temp[5];


void setup() {
 // Serial.begin(9600);
  s7s.begin(9600);
  clearDisplay();
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  s7s.print("-_-_");
  delay(900);
  s7s.print("_-_-");
  delay(900);
  s7s.print("8888");
  delay(900);
  setDecimals(0b11111111);
  delay (800);
  setDecimals(0b00000000);
  delay(1500);
}

void loop() {
  tmElements_t tm;
  
  sensor = analogRead(analogInPin); 
  val = map(sensor, 0, 1023, 0, 255);
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  SensorValue1 = analogRead(LM35);
  SensorValue2 = analogRead(LM352);
  temp[1] = (5.0 * analogRead(LM35) * 100.0) / 1024;
  temp[2] = (5.0 * analogRead(LM352) * 100.0) / 1024;
  temperatur = (temp[1]+temp[2])/2-2;

  (RTC.read(tm));
   if (buttonState1 == HIGH) { 
     
    setDecimals(0b00000000);
    sprintf(tempString, "%4d", temperatur);
    s7s.print(temperatur,0),s7s.write(0x7D),s7s.write("C");
    setDecimals(0b00100000); 
  delay(2000);
 }
 if (buttonState2 == HIGH) {
  //animation();
  //delay(2000);
  clearDisplay();
  kalender();
  
  
 }
  else {
    setDecimals(0b00010000);
    print2digits(tm.Hour);
    print2digits(tm.Minute);
    setBrightness(val);
  delay(1000);
 }
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
  s7s.print('0');
  }
  s7s.print(number);
}

void setDecimals(byte decimals)
{
  s7s.write(0x77);
  s7s.write(decimals);
}

void clearDisplay()
{
  s7s.write(0x76);  // Clear display command
}

void setBrightness(byte value)
{
  s7s.write(0x7A);  // Set brightness command byte
  //s7s.write(value);  // brightness data byte
  s7s.write(val);
}

void animation()
{
  setDecimals(0b00000000); 
  s7s.print("-_-_");
  delay(900);
  s7s.print("_-_-");
  delay(900);
  s7s.print("8888");
  delay(900);
  setDecimals(0b11111111);
  delay (800);
  setDecimals(0b00000000);
  delay(800);
  setDecimals(0b11111111);
  delay (800);
  setDecimals(0b00000000);
  delay(800);
  s7s.print("   0");
  delay(800);
  s7s.print("  0 ");
  delay(800);
  s7s.print(" 0  ");
  delay(800);
  s7s.print("0   ");
  delay(800);
  s7s.print(" 0  ");
  delay(800);
  s7s.print("  0 ");
  delay(800);
  s7s.print("   0");
  delay(800);
  
}

void kalender()
{
  tmElements_t tm;
  (RTC.read(tm));
  setDecimals(0b00000000);
  s7s.print("CAL ");
  delay(2000);
 // clearDisplay();
  delay(2000);
  setDecimals(0b00000010);
  print2digits(tm.Day);
  print2digits(tm.Month);
  delay(2000);
  setDecimals(0b00000000);
  s7s.print(tmYearToCalendar(tm.Year));
  delay(2000);
}
  
