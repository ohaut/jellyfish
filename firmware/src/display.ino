#include <Adafruit_NeoPixel.h>

#define PIN            4
#define NUMPIXELS      256
#define DELAYVAL       10


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t display[16][16];

const int matrix_x_start[4]={0, 8, 0, 8};
const int matrix_y_start[4]={0, 0, 8, 8};

#define NUMMATRIXES 4

void setup_display() {
    pixels.begin();
}

void translate_display() {
    int x, y, xs, ys, pixel;
    int mat;

    pixel=0;
    for (mat=0; mat<NUMMATRIXES; mat++) {
        xs = matrix_x_start[mat];
        ys = matrix_y_start[mat];
        for (y=0; y<8; y++) {
            for (x=0; x<8; x++) {
                pixels.setPixelColor(pixel++, display[ys+y][xs+x]);
            }
        }
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
    memset(display,0,sizeof(display));
}

#define FONT_ROWS 5
// 0123456789:
const char* numbers[FONT_ROWS]={
    " #   # ## ## # # ##  #  ### ### ###   ##  # ",
    "# # ##  #  # # # #  #     # # # # # # #  #  ",
    "# #  # ## ## ### ## ##   #  ### ###     #   ",
    "# #  # #   #   #  # # #  #  # #   # #  #  # ",
    " #   # ## ##   # ##  #   #  ###   #   #  ## "};
const int digit_cols[]={4,3,3,3,4,3,4,4,4,4,2,5};

void draw_pixel(int x, int y, uint32_t color){
    if (x>=0 && x<16 && y>=0 && y<16)
        display[y][x] = color;
}

int char_to_idx(char digit) {
  int idx =-1;
  if (digit>='0' && digit<='9') idx = digit-'0';
  if (digit==':') idx=10;
  if (digit=='%') idx=11;
  return idx;
}

int char_length(char chr) {
  int idx = char_to_idx(chr);
  if (idx<0) return 0;
  return digit_cols[idx];
}

int draw_length(char *str) {
    int width = 0;
    while (*str)
      width += char_length(*str++);
    return width - 1;
}


int center_ofs(char *str) {
    int width = 16 - draw_length(str);
    return width / 2;
}

int right_ofs(char *str) {
    return 15 - draw_length(str);
}

int draw_digit(int x, int y, char digit, uint32_t color) {
  int idx = char_to_idx(digit);

  if (idx<0) return 0;
  int start_col = 0;

  for (int i=0;i<idx; i++)
     start_col += digit_cols[i];
  for (int yf=0; yf<FONT_ROWS; yf++)
      for (int xf=0; xf<digit_cols[idx]; xf++) {
        if (numbers[yf][xf+start_col] != ' ')
            draw_pixel(x+xf, y+yf, color);
    }

    return digit_cols[idx];
 }

int draw_string(int x, int y, const char *str, uint32_t color) {
    int width;
    while(*str && x<16) {
        width = draw_digit(x, y, *str++, color);
        x += width;
    }
}
