#include "utils.h"
#include "engine_defs.h"

void GetRGB(Uint32 color, Uint8* r, Uint8* g, Uint8* b){
    *r = (color & (255 << 24)) >> 24;
    *g = (color & (255 << 16)) >> 16;
    *b = (color & (255 << 8)) >> 8;
    // printf("%x, %x, %x\n", color, 255 << 24, color & (255<<24));
    // printf("%d, %d, %d\n", *r, *g, *b);
}

double lerp(double x, double y, double p){
    return x + p*(y-x);
}


void ResetDepthBuffer(){
    for (int x=0; x<*WINDOW_WIDTH; x++){
        for (int y=0; y<*WINDOW_HEIGHT; y++){
            DEPTH_BUFFER[y**WINDOW_WIDTH + x] = 99999999.;
        }
    }
    *MAX_DEPTH = -9999999999;
    *MIN_DEPTH = 9999999999;
}