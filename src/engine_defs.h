#ifndef _DEFS
#define _DEFS

#include <math.h>

#define RES *WINDOW_WIDTH * *WINDOW_HEIGHT
#define FOV 45



extern int* WINDOW_WIDTH;
extern int* WINDOW_HEIGHT;
extern int* WINDOW_BPP;

extern double* Z0;



void init_engine();
#endif