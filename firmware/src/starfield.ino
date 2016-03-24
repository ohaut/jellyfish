
#define MAX_STARS 15

typedef struct
{
	float x, y, xspeed, yspeed;
    uint32_t color;
} star_type;

star_type stars[MAX_STARS];

float frand() {
  return ((float)(1024-(rand()%2048)))/8192.0;
}

float crand(int max=32) {
    max++; // avoid division by 0
    return color(1+rand()%max, 1+rand()%max, 1+rand()%max);
}

void init_starfield() {
    for(int i=0;i<MAX_STARS;i++){
        stars[i].x=rand()%16;
        stars[i].y=rand()%16;
        stars[i].xspeed = frand(); // change 16 for diff effects
        stars[i].yspeed = frand(); // change 16 for diff effects
    }
}
void run_starfield() {

    for(int i=0;i<MAX_STARS;i++){
          int val;
          stars[i].x += stars[i].xspeed;
          stars[i].y += stars[i].yspeed;

          if((stars[i].x <= 0)||
             (stars[i].x >= 16) ||
             (stars[i].y <= 0)||
             (stars[i].y >= 16))
             {
               stars[i].x=8;
               stars[i].y=7;
               stars[i].xspeed = frand(); // change 16 for diff effects
               stars[i].yspeed = frand(); // change 16 for diff effects
               val =(fabs(stars[i].xspeed) + fabs(stars[i].yspeed))*64.0;
               stars[i].color = crand(val);
             }
            draw_pixel((int)stars[i].y, (int)stars[i].x, stars[i].color);
      }
}
