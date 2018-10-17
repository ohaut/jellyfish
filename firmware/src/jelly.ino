
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


void animation_1(float f, float brightness) {

  float fs,fp;
  float R,G,B;
  int s,p;

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
  
}
void animation_2(float f, float brightness) {

  float fs,fp;
  float R,G,B;
  int s,p;

  for (s=0;s<8;s++)
  for (p=0;p<7;p++) {

    fp = p; // height (top to bottom)
    fs = s; // angle

    fp=(fp/7)*3.1415+f;
    fs=(fs/8)*3.1415;

    R = sin(fp)+1.0;
    G = cos(fp*1.2)+1.0;
    B = sin(fp*1.4)+1.0;

    jelly_pixel(s, p, color(brightness*fabs(R), brightness*fabs(G), brightness*fabs(B)));

  }
  
}
void animation_3(float f, float brightness) {

  float f_bright;
  float fs,fp;
  float R,G,B;
  int s,p;

  for (s=0;s<8;s++)
  for (p=0;p<7;p++) {

    fp = p; // height (top to bottom)
    fs = s; // angle

    fp=(fp/7)*3.1415;
    fs=(fs/8)*3.1415;

    R = sin(fp+f)+1.0;
    G = cos((fp+f)*1.2)+1.0;
    B = sin((fp+f)*1.4)+1.0;

    f_bright = brightness * (sin((fp*3.0)+f*0.5));

    if (f_bright<0.0) f_bright=0.0;

    jelly_pixel(s, p, color(f_bright*fabs(R), f_bright*fabs(G), f_bright*fabs(B)));

  }
  
}

void loop() {

  static float f=0.0;
  float brightness=100.0;
  
  f=f-0.04;
  if (f<-314.15) f=314.15;

  clear_display();

  animation_3(f, brightness);

  show_display();
 
  ArduinoOTA.handle();

}
