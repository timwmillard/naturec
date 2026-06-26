#include "nature.h"
#include "raylib.h"

const int width = 640;
const int height = 240;
const char *window_title = "Nature of Code - Example Perlin Noise";

float x = (float)width / 2;
float y = (float)height / 2 - 20;

float xr = (float)width / 2;
float yr = (float)height / 2 + 20;

float xoff = 0;

void setup(void) {
   ClearBackground(GRAY);
}

void draw(void) {
   ClearBackground(GRAY);

   x = map(noise(xoff, 0, 0), 0, 1, 0, width);
   xoff += 0.01;
   DrawCircle(x, y, 20, DARKGRAY);

   xr = randomMax(width);
   DrawCircle(xr, yr, 20, DARKGRAY);
}
