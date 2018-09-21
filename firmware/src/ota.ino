
#include <ArduinoOTA.h>

void setup_ota_upgrades() {
  ArduinoOTA.begin();

  // All this is optional fancy to display upgrade progress
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    int s=0;
    int p=0;

    clear_display();
    for(int i=0;i<progress/(total/(SIDES*PIX_SIDE));i++) {
       jelly_pixel(s,p, color(0,10,0));
       p=p+1;
       if (p>=PIX_SIDE) {
  	   p=0;
           s=s+1;
       }
    }
    show_display();
  });

//  ArduinoOTA.onEnd([]() {
//   for(int i=0;i<NUMPIXELS;i++) draw_pixel(i%16, i/16, 0);
//    show_display();
//  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.print("OTA_ERROR: ");
    Serial.print(error);
    Serial.print("\n");  
    int s=0;
    int p=0;

    clear_display();
    for(int i=0;i<SIDES*PIX_SIDE;i++) {
       jelly_pixel(s,p, color(10,0,0));
       p=p+1;
       if (p>=PIX_SIDE) {
  	   p=0;
           s=s+1;
       }
    }
    show_display();
    delay(1000);
  });
}
