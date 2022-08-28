#ifndef _DEFS
#define _DEFS

#include <math.h>
#include "vector.h"

#define RES *WINDOW_WIDTH * *WINDOW_HEIGHT
#define FOV 60

#define DRAWMODE_WIREFRAME 0
#define DRAWMODE_TRIANGLE 1
#define DRAWMODE_BOTH 2
#define DRAWMODE_DEPTH 3


extern int* WINDOW_WIDTH;
extern int* WINDOW_HEIGHT;
extern int* WINDOW_BPP;

extern double* Z0;

extern double* DEPTH_BUFFER;
extern double* MAX_DEPTH;
extern double* MIN_DEPTH;

extern Vec3* ROTATION;



void init_engine();
#endif