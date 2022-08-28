#include "utils.h"
#include "engine_defs.h"

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