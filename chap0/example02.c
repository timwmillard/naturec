#include <math.h>

#include "nature.h"
#include "raylib.h"

const int width = 640;
const int height = 240;
const char *window_title = "Nature of Code - Example 0.2 random histogram";

const int total = 20;
static int randomCounts[20] = {0};

void setup(void) {
   ClearBackground(WHITE);

   for (int i = 0; i < total; i++) {
      randomCounts[i] = 0;
   }
}

void draw(void) {
   ClearBackground(WHITE);
   const int index = floor(randomMax(total));
   randomCounts[index]++;

   Color fillColor = (Color){127, 127, 127, 255};

   const int w = width / total;
   for (int x = 0; x < total; x++) {
      DrawRectangle(x * w, height - randomCounts[x], w - 1, randomCounts[x],
                    fillColor);
      DrawRectangleLinesEx(
          (Rectangle){
              x * w,
              height - randomCounts[x],
              w - 1,
              randomCounts[x],
          },
          2, BLACK);
   }
}
