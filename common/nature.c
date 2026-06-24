// The Nature of Code -- shared sketch runner.
//
// Provides main() and the persistent-canvas loop so each example only has to
// supply setup()/draw() and the noc_* config globals (see noc.h).

#include <time.h>
#include <math.h>

#include "raylib.h"
#include "nature.h"

// raylib bundles stb_perlin (it backs GenImagePerlinNoise) and compiles it into
// libraylib.a, but doesn't declare it in raylib.h. Declare the symbol ourselves
// and let the linker resolve it against raylib's copy. Returns ~[-1, 1]. The
// seed is an offset into stb's permutation table (0..255); seed 0 matches the
// unseeded stb_perlin_noise3.
extern float stb_perlin_noise3_seed(float x, float y, float z,
                                    int x_wrap, int y_wrap, int z_wrap, int seed);

static int noise_seed = 0;

float randomf(void) {
    // raylib's GetRandomValue is integer-only; scale a 0..999999 draw down to
    // [0, 1). 1000000 (not 999999) as the divisor keeps it exclusive of 1.
    return (float)GetRandomValue(0, 999999) / 1000000.0f;
}

float randomMax(float max) {
    return randomf() * max;
}

float randomRange(float min, float max) {
    return min + randomf() * (max - min);
}

float noise(float x, float y, float z) {
    // stb returns roughly [-1, 1]; remap to p5's [0, 1) and clamp the rare
    // out-of-range sample so callers can rely on the bound.
    float n = (stb_perlin_noise3_seed(x, y, z, 0, 0, 0, noise_seed) + 1.0f) * 0.5f;
    if (n < 0.0f) n = 0.0f;
    if (n > 1.0f) n = 1.0f;
    return n;
}

float randomGaussian(float mean, float sd) {
  static bool hasSpare = false;
  static float spare;

  if (hasSpare) {
      hasSpare = false;
      return spare * sd + mean;
  }

  float u1 = (float)GetRandomValue(1, 1000000) / 1000000.0f;
  float u2 = (float)GetRandomValue(1, 1000000) / 1000000.0f;
  float mag = sqrtf(-2.0f * logf(u1));

  spare = mag * sinf(2.0f * PI * u2);   // save the second
  hasSpare = true;
  return mag * cosf(2.0f * PI * u2) * sd + mean;  // return the first
}

int main(void) {
    SetRandomSeed((unsigned int)time(NULL));
    noise_seed = GetRandomValue(0, 255);  // randomize Perlin noise per run too
    InitWindow(width, height, window_title);
    SetTargetFPS(60);

    // Persistent canvas: p5 keeps what you draw between frames, but raylib
    // double-buffers, so we accumulate into an off-screen render texture.
    RenderTexture2D canvas = LoadRenderTexture(width, height);

    BeginTextureMode(canvas);
        setup();
    EndTextureMode();

    while (!WindowShouldClose()) {
        BeginTextureMode(canvas);
            draw();
        EndTextureMode();

        BeginDrawing();
            // Render textures are stored flipped vertically; negative source
            // height flips it back to screen orientation.
            DrawTextureRec(canvas.texture,
                (Rectangle){ 0, 0, (float)canvas.texture.width, -(float)canvas.texture.height },
                (Vector2){ 0, 0 }, WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(canvas);
    CloseWindow();

    return 0;
}
