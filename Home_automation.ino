#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>

char auth[] = "";
char ssid[] = "";
char pass[] = "";

int pirpin = D1;
int irpin = D2;
int smokepin = A0;
int buzzer = D4;
int led = D5;
int s;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
  pinMode(pirpin,INPUT);
  pinMode(irpin,INPUT);
  pinMode(smokeD0,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT); 

  Blynk.notify("Connected");
}

BLYNK_WRITE(V2)
{
  s = param.asINT();
}

void loop()
{
  Blynk.run();
  int ir = digitalRead(irpin);
  int pir = digitalRead(pirpin);
  int smoke = digitalRead(smokepin);
  
  if(ir == LOW)
  {
    Blynk.virtualWrite(V0,"Garage open!");
    digitalWrite(led,HIGH);
    if(s == HIGH)
    {
      if(pir == LOW)
    {
      Blynk.notify("Intruder detected");
      digitalWrite(buzzer,HIGH);
    }
    else if(pir == HIGH)
    {
      digitalWrite(buzzer,LOW);
    }
    }
    if(smoke <= 600)
    {
      Blynk.virtualWrite(V1,"Smoke detected");
    }
    else
    {
      Blynk.virtualWrite(V1," ");
    }
  }
  else if(ir == HIGH)
  {
    Blynk.virtualWrite(V0,"Garage closed!");
    if(pir == LOW)
    {
      Blynk.notify("Intruder detected");
      digitalWrite(buzzer,HIGH);
    }
    else if(pir == HIGH)
    {
      digitalWrite(buzzer,LOW);
    }

    if(smoke <= 600)
    {
      Blynk.virtualWrite(V1,"Smoke detected");
    }
    else
    {
      Blynk.virtualWrite(V1," ");
    }
  }
}
