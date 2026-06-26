#include <math.h>

#include "nature.h"
#include "raylib.h"

const int width = 640;
const int height = 240;
const char *window_title = "Nature of Code - Example 0.1 random walker";

typedef struct {
   int x;
   int y;
} Walker;

static Walker walker;

void walker_show(Walker *walker) {
   DrawPixel(walker->x, walker->y, BLACK);
}

void walker_step(Walker *walker) {
   const int choice = floor(randomMax(4));
   if (choice == 0) {
      walker->x++;
   } else if (choice == 1) {
      walker->x--;
   } else if (choice == 2) {
      walker->y++;
   } else {
      walker->y--;
   }
}

void setup(void) {
   walker.x = width / 2; // new Walker()
   walker.y = height / 2;
   ClearBackground(WHITE);
}

void draw(void) {
   walker_step(&walker);
   walker_show(&walker);
}
