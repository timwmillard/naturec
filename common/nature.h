// The Nature of Code -- shared sketch runner.
//
// Include this from an example and provide:
//   - the sketch config globals (noc_width, noc_height, noc_title)
//   - setup(void): runs once, into the persistent canvas (like p5 setup())
//   - draw(void):  runs every frame, into the persistent canvas (p5 draw())
//
// main() lives in the noc library (common/noc.c) and drives the loop, so each
// example is just state + setup + draw.
#ifndef NOC_H
#define NOC_H

#define map(value, start1, stop1, start2, stop2)                               \
   (((value) - (start1)) / ((stop1) - (start1)) * ((stop2) - (start2)) +       \
    (start2))

// --- Sketch contract: defined by each example -------------------------------

// Window configuration. Read once by the runner before the window is created.
extern const int width;
extern const int height;
extern const char *window_title;

// Like p5's setup()/draw(). Both run with the persistent canvas bound, so
// anything you draw accumulates between frames unless you clear it yourself.
void setup(void);
void draw(void);

// --- Shared helpers ---------------------------------------------------------

// p5's random(): returns a value in [0, 1).
float randomf(void);

// p5's random(max): returns a value in [0, max).
float randomMax(float max);

// p5's random(min, max): returns a value in [min, max).
float randomRange(float min, float max);

// p5's randomGaussian(mean, sd): normally distributed value.
float randomGaussian(float mean, float sd);

// p5's noise(x, y, z): Perlin noise in [0, 1). Pass 0 for unused dimensions,
// e.g. Noise(t, 0, 0) for 1D or Noise(x, y, 0) for 2D. The runner randomizes
// the underlying permutation at startup, so the field differs each run.
float noise(float x, float y, float z);

#endif // NOC_H
