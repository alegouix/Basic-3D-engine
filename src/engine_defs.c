#include "engine_defs.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <SDL2/SDL_image.h>

int* WINDOW_WIDTH;
int* WINDOW_HEIGHT;
int* WINDOW_BPP;
double* Z0;
double* DEPTH_BUFFER;
double* MAX_DEPTH;
double* MIN_DEPTH;
Vec3* ROTATION;
SDL_Surface* CRATE_TEXTURE;

void init_engine(){

    WINDOW_WIDTH = (int*)malloc(sizeof(int));
    WINDOW_HEIGHT = (int*)malloc(sizeof(int));
    WINDOW_BPP = (int*)malloc(sizeof(int));
    Z0 = (double*)malloc(sizeof(double));
    MAX_DEPTH = (double*)malloc(sizeof(double));
    MIN_DEPTH = (double*)malloc(sizeof(double));
    ROTATION = (Vec3*)malloc(sizeof(Vec3));

    if (WINDOW_WIDTH == NULL || WINDOW_HEIGHT == NULL || WINDOW_BPP == NULL || Z0 == NULL || ROTATION == NULL || MAX_DEPTH == NULL || MIN_DEPTH == NULL){
        printf("ERROR %d while initialising engine\n", errno);
        return;
    }

    *WINDOW_WIDTH = 1200;
    *WINDOW_HEIGHT = 900;
    DEPTH_BUFFER = (double*)calloc(*WINDOW_WIDTH**WINDOW_HEIGHT, sizeof(double));
    if (DEPTH_BUFFER == NULL){
        printf("ERROR %d while initialising engine\n", errno);
        return;
    }

    *WINDOW_BPP = 32;
    *Z0 = (*WINDOW_WIDTH/2)/tan((FOV/2) * M_PI / 180.0);
    *ROTATION = NewVec3(0, 0, 0);
    *MAX_DEPTH = 0;

    ResetDepthBuffer();//memset(DEPTH_BUFFER, 0, *WINDOW_WIDTH**WINDOW_HEIGHT);


    CRATE_TEXTURE = IMG_Load("textures/crate-texture.jpg");
    if (CRATE_TEXTURE == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
        return;
    }

}