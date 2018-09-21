#include <Adafruit_NeoPixel.h>

#define PIN            4
#define PIX_SIDE 7
#define SIDES 	 8
#define BOTTOM  5
#define NUMPIXELS      (PIX_SIDE * SIDES + BOTTOM)
#define DELAYVAL       10


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t jelly[SIDES][PIX_SIDE];
uint32_t jelly_bottom[BOTTOM];

#define NUMMATRIXES 4

void setup_display() {
    pixels.begin();
}

void jelly_pixel(int side, int pix, uint32_t color) {
   if ((side>=SIDES) || (pix >= PIX_SIDE))
	return;

   jelly[side][pix] = color;
}

void translate_display() {
    int side, pix;
    int pixel=0;
    for (side=0; side<SIDES; side++) {
	for (pix=0; pix<PIX_SIDE; pix++) {		
                pixels.setPixelColor(pixel++, jelly[side][pix]);
        }
    }

    for (pix=0; pix<BOTTOM; pix++) {
        pixels.setPixelColor(pixel++, jelly_bottom[pix]);
    }
}

void show_display() {
    translate_display();
    pixels.show();
    delay(DELAYVAL);
}

uint32_t color(int r, int g, int b) {
    return pixels.Color(r,g,b);
}
void clear_display() {
    memset(jelly,0,sizeof(jelly));
    memset(jelly_bottom,0,sizeof(jelly_bottom));
}
