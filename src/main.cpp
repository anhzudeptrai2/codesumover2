#include <Arduino.h>
int RPWM1 = 7; // động cơ trái
int LPWM1 = 6;
int RPWM = 8; // động cơ phải
int LPWM = 9;

int IRFL = 2;  // IR trước trai
int IRFR = 3;  // IR truoc phai
int IRCB = 21; // IR sau

int trig1 = 4; // SR trướcttttt
int echo1 = 5;
int trig2 = 12; // SR phải
int echo2 = 13;
int trig3 = 10; // SR trái
int echo3 = 11;

int Button = 22;
int valButton;

int valIRFL;
int valIRFR;
int valIRCB;

unsigned long duration1, duration2, duration3;

int distance1;
int distance2;
int distance3;

void FORWARD()
{
  Serial.println("Tien");
  analogWrite(LPWM, 155);
  analogWrite(LPWM1, 155);
  analogWrite(RPWM, 0);
  analogWrite(RPWM1, 0);
}

void BACKWARD()
{
  Serial.println("Lui");
  analogWrite(LPWM, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM, 155);
  analogWrite(RPWM1, 155);
}

void Stop()
{
  Serial.println("Dung");
  analogWrite(LPWM, 0);
  analogWrite(RPWM, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM1, 0);
}

void Rotate()
{
  Serial.println("Rotate"); // xoay tại chỗ
  analogWrite(LPWM, 100);
  analogWrite(RPWM, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM1, 100);
}
void RightBackWard()
{
  Serial.println("lui phai");
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 100);
  analogWrite(RPWM1, 0);
  analogWrite(LPWM1, 50);
}
void LeftBackWard()
{
  Serial.println("lui trai");
  analogWrite(RPWM, 0);
  analogWrite(RPWM1, 0);
  analogWrite(LPWM, 50);
  analogWrite(LPWM1, 100);
}
void RightForWard()
{
  Serial.println("tien phai");
  analogWrite(RPWM, 100);
  analogWrite(RPWM1, 50);
  analogWrite(LPWM, 0);
  analogWrite(LPWM1, 0);
}
void LeftForWard()
{
  Serial.println("tien trai");
  analogWrite(RPWM, 50);
  analogWrite(RPWM1, 100);
  analogWrite(LPWM, 0);
  analogWrite(LPWM, 0);
}
void Push()
{
  analogWrite(LPWM, 255);
  analogWrite(RPWM, 0);
  analogWrite(LPWM1, 255);
  analogWrite(RPWM1, 0);
}
void search()
{
   int scan = 0;
   if (distance1 <= 25) // SR trước
  {
    Serial.println(" dam bang dau");
    Push();
  }
  else if (distance2 <= 25) // SR Trái
  {
    Serial.println("re trai r dam");
    LeftForWard();
    Push();
  }
  else if (distance3 <= 25) // SR Phai
  {
    Serial.println("re phai roi dam");
    RightForWard();
    Push();
  }

  else
  {
    if (scan < 3)
    {
      analogWrite(RPWM, 80);
      analogWrite(LPWM, 0);
      analogWrite(RPWM1, 0);
      analogWrite(LPWM1, 50);
    }
    else if (scan <= 5)
    {
      analogWrite(RPWM, 0);
      analogWrite(LPWM, 80);
      analogWrite(RPWM1, 50);
      analogWrite(LPWM1, 0);
    }
    if (scan < 5)
    {
      scan += 1;
    }
    else if (scan == 5)
    {
      scan = 0;
    }
  }
}

boolean caseInterrupt0 = false;
boolean caseInterrupt1 = false;
boolean caseInterrupt2 = false;

long timechange = 0;

void proval()
{
  unsigned time = 500;
  while (caseInterrupt0 && millis() - timechange < time)
    ;
  while (caseInterrupt1 && millis() - timechange < time)
    ;
  while (caseInterrupt2 && millis() - timechange < time)
    ;
  // khai bao ham valIR
  valIRFR = digitalRead(IRFR);
  valIRFL = digitalRead(IRFL);
  valIRCB = digitalRead(IRCB);

  caseInterrupt0 = false; // reset TH ngat
  caseInterrupt1 = false;
  caseInterrupt2 = false;
}
void Interrupt0() // IRFR == 0
{
  Stop();
  delay(50);
  LeftBackWard();
  search();
  caseInterrupt0 = true;
  timechange = millis();

  caseInterrupt1 = false;
  caseInterrupt2 = false;
}
void Interrupt1() // IRFL == 0
{
  Stop();
  delay(50);
  RightBackWard();
  search();
  caseInterrupt1 = true;
  timechange = millis();
  caseInterrupt0 = false;
  caseInterrupt2 = false;
}
void Interrupt2() // IRCB == 0
{
  Stop();
  delay(50);
  FORWARD();
  search();
  caseInterrupt2 = true;
  timechange = millis();
  caseInterrupt0 = false;
  caseInterrupt1 = false;
}
void setup()
{
  Serial.begin(9600);
  delay(1000);
  // dong co
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  // IR
  pinMode(IRFL, INPUT);
  pinMode(IRFR, INPUT);
  pinMode(IRCB, INPUT);
  // SR
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  // chay ham ngat
  attachInterrupt(0, Interrupt0, RISING);
  attachInterrupt(1, Interrupt1, RISING);
  attachInterrupt(2, Interrupt2, RISING);
}

void loop()
{
  // IR truoc phai
  valIRFR = digitalRead(IRFR);
  Serial.print("IR truoc phai: ");
  Serial.println(valIRFR);
  // IR truoc trai
  valIRFL = digitalRead(IRFL);
  Serial.print("IR truoc trai: ");
  Serial.println(valIRFL);
  // IR sau
  valIRCB = digitalRead(IRCB);
  Serial.print("IR trung tam: ");
  Serial.println(valIRCB);
  // SR04 truoc
  digitalWrite(trig1, 0);
  delayMicroseconds(2);
  digitalWrite(trig1, 1);
  delayMicroseconds(5);
  digitalWrite(trig1, 0);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = int(duration1 / 2 / 29.412);
  // SR phai
  digitalWrite(trig2, 0);
  delayMicroseconds(2);
  digitalWrite(trig2, 1);
  delayMicroseconds(5);
  digitalWrite(trig2, 0);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = int(duration2 / 2 / 29.412);
  // SR trai
  digitalWrite(trig3, 0);
  delayMicroseconds(2);
  digitalWrite(trig3, 1);
  delayMicroseconds(5);
  digitalWrite(trig3, 0);
  duration3 = pulseIn(echo3, HIGH);
  distance3 = int(duration3 / 2 / 29.412);

  if (distance1 >= 1 && distance1 <= 25)
  {
    Serial.print(distance1);
    Serial.println("cm");
  }
  else
  {
    Serial.println("value cannot be read");
  }
  if (distance2 >= 1 && distance2 <= 15)
  {
    Serial.print(distance2);
    Serial.println("cm");
  }
  else
  {
    Serial.println("value cannot be read");
  }
  if (distance3 >= 1 && distance3 <= 15)
  {
    Serial.print(distance3);
    Serial.println("cm");
  }
  else
  {
    Serial.println("value cannot be read");
  }
  delay(1000);
}
