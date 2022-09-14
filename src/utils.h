#ifndef _UT
#define _UT 1

#include <SDL2/SDL.h>

typedef struct {
    double x,y;
} Point2D;

double lerp(double x, double y, double p);
void ResetDepthBuffer();
void GetRGB(Uint32 color, Uint8* r, Uint8* g, Uint8* b);

#endif