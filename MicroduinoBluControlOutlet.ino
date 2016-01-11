#include "key.h"

#include <SoftwareSerial.h>

#define outletPin 6
#define led_Pin 5
#define Button_Pin 4

SoftwareSerial mySerial(2, 3); //RX,TX

#define my_Serial mySerial
//#define my_Serial Serial1  //Core+

String tmp="";

boolean swith,change;

void setup() {
  Serial.begin(9600);
  Serial.println("LEDOnOff Starting...");
  my_Serial.begin(9600);

  pinMode(outletPin, OUTPUT);
  pinMode(led_Pin, OUTPUT);
  pinMode(Button_Pin, INPUT_PULLUP);
  digitalWrite(outletPin,LOW);
  digitalWrite(led_Pin,HIGH);

  key_init();
}

void loop() {
  // if there's any serial available, read it:
  while (my_Serial.available() > 0) {

    tmp += char(my_Serial.read());
    delay(2);
  }

  if (tmp.length() > 0) {
    if(tmp=="on") {
      Serial.println("power on");
      digitalWrite(outletPin,HIGH);
      swith=true;
    } 
    else if(tmp=="off") {
      digitalWrite(outletPin,LOW);
      Serial.println("power off");
      swith=false;
    }
    tmp = "";
  }

  if(key_get(Button_Pin,0))
  {
    delay(300);
    swith=!swith;
  }

  if(change!=swith)
  {
    change=swith;
    if(swith)
    {
      digitalWrite(outletPin,HIGH);
      my_Serial.println("ON");
    }
    else
    {
      digitalWrite(outletPin,LOW);
      my_Serial.println("OFF");
    }
  }
}


