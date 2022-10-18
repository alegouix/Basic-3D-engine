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

/* https://stackoverflow.com/questions/53033971/how-to-get-the-color-of-a-specific-pixel-from-sdl-surface */
Uint32 getpixel(SDL_Surface *surface, int x, int y){
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp){
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN){
                return p[0] << 16 | p[1] << 8 | p[2];
            }
            else{
                return p[0] | p[1] << 8 | p[2] << 16;
                break;
            }

            case 4:
                return *(Uint32 *)p;
                break;

            default:
                return 0;       /* shouldn't happen, but avoids warnings */
        }
}