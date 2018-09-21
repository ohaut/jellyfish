
#include <Adafruit_NeoPixel.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <math.h>

#define AP   "laotrainternet2"
#define PASS "yavaledehackers33"
void setup() {

  Serial.begin(115200);
  Serial.print("hello, I'm a jellyfish!");
  WiFi.mode(WIFI_STA);
  WiFi.begin(AP, PASS);
  setup_display();
  setup_ota_upgrades();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  for (int i=0;i<100;i++) {
    ArduinoOTA.handle();
    delay(25);
  }

}

void loop() {

  static float f=0.0;
  float brightness=200.0;
  
  float fs,fp;
  float R,G,B;
  int s,p;

  clear_display();

  f=f-0.04;

  if (f<-314.15) f=314.15;

  for (s=0;s<8;s++)
  for (p=0;p<7;p++) {

    fp = p; // height (top to bottom)
    fs = s; // angle

    fp=(fp/7)*3.1415+f;
    fs=(fs/8)*3.1415;

    R = sin(fp);
    G = cos(fp*1.2);
    B = sin(fp*1.4);

    jelly_pixel(s, p, color(brightness*fabs(R), brightness*fabs(G), brightness*fabs(B)));


  }
  
  if (p>=7) {
      p=0;
      s+=1;
  } 
  if (s>=8) {
      s= 0;
  }

  show_display();

  ArduinoOTA.handle();
}
