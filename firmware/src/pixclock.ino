
#include <Adafruit_NeoPixel.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

#define AP   "myap"
#define PASS "mypassss"
void setup() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(AP,PASS);
  setup_display();
  setup_ota_upgrades();
  init_starfield();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  for (int i=0;i<100;i++) {
    ArduinoOTA.handle();
    delay(25);
  }

  ntp_begin();
}

void loop() {

  char str[16];
  int h,m,s,brightness;
  bool day_mode;

  h = hour();
  m = minute();
  s = second();

  clear_display();

  day_mode = (h>8) && (h<21);

  if (day_mode) {
    run_starfield();
    brightness = 8;
  } else {
    brightness = 1;
  }

  sprintf(str, "%2d:%02d", h, m);

  draw_string(center_ofs(str),5,str, color(brightness,0,0));
  draw_pixel(s%16,11+s/16, color(brightness,0,0));

  show_display();

  ArduinoOTA.handle();
}
