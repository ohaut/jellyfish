
#include <Adafruit_NeoPixel.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

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

  int brightness;
  static int p=0;
  static int s=0;

  clear_display();

  brightness = 10;

  jelly_pixel(s, p++, color(brightness, p*20, p*20));

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
