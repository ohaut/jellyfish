
#include <ArduinoOTA.h>

void setup_ota_upgrades() {
  ArduinoOTA.begin();

  // All this is optional fancy to display upgrade progress
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    clear_display();
    for(int i=0;i<(progress/(total/NUMPIXELS));i++)
      draw_pixel(i/16,i%16, color(0,1,0));
    char str[8];
    sprintf(str, "%d%%", (progress * 100)/total);
    draw_string(right_ofs(str),5,str, color(8,8,8));
    show_display();
  });

//  ArduinoOTA.onEnd([]() {
//   for(int i=0;i<NUMPIXELS;i++) draw_pixel(i%16, i/16, 0);
//    show_display();
//  });

  ArduinoOTA.onError([](ota_error_t error) {
      for(int i=0;i<NUMPIXELS;i++)
        draw_pixel(i%16, i/16, color(8,0,0));
      show_display();
      delay(1000);
    });
}
