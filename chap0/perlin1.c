#include "nature.h"
#include "raylib.h"

const char *window_title = "Nature of Code - Example Perlin Noise";

float x;
float y;

float xr;
float yr;

float xoff = 0;

void setup(void) {
   createCanvas(640, 240);
   ClearBackground(GRAY);

   x = (float)width / 2;
   y = (float)height / 2 - 20;

   xr = (float)width / 2;
   yr = (float)height / 2 + 20;
}

void draw(void) {
   ClearBackground(GRAY);

   x = map(noise(xoff, 0, 0), 0, 1, 0, width);
   xoff += 0.01;
   DrawCircle(x, y, 20, DARKGRAY);

   xr = randomMax(width);
   DrawCircle(xr, yr, 20, DARKGRAY);
}
