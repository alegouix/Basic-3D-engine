#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "engine_defs.h"
#include "draw.h"
#include "point.h"

SDL_Window* screen = NULL;
SDL_Renderer* renderer = NULL;

int init(){
    init_engine();
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        return -1;
    }

    screen = SDL_CreateWindow("3D",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *WINDOW_WIDTH, *WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (screen == NULL){
        return -1;
    }

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        return -1;
    }


    return 0;

}

void Quit(){
    SDL_Quit();
}

int mainloop(SDL_Window* screen, SDL_Renderer* renderer){
    int running=1;
    SDL_Event event;


    int n_points = 8;
    Point** points = (Point**)calloc(n_points, sizeof(Point*));
    double d=300;
    points[0] = NewPoint(d, d, d);
    points[1] = NewPoint(d, d, -d);
    points[2] = NewPoint(d, -d, d);
    points[3] = NewPoint(d, -d, -d);
    points[4] = NewPoint(-d, d, d);
    points[5] = NewPoint(-d, d, -d);
    points[6] = NewPoint(-d, -d, d);
    points[7] = NewPoint(-d, -d, -d);

    int n_lines = 12;
    int **lines = (int**)calloc(n_lines, sizeof(int*));
    for (int i=0; i<n_lines; i++){
        lines[i] = (int*)calloc(2, sizeof(int));
    }
    lines[0][0] = 0;
    lines[0][1] = 1;
    lines[1][0] = 0;
    lines[1][1] = 2;
    lines[2][0] = 0;
    lines[2][1] = 4;
    lines[3][0] = 1;
    lines[3][1] = 3;
    lines[4][0] = 1;
    lines[4][1] = 5;
    lines[5][0] = 2;
    lines[5][1] = 3;
    lines[6][0] = 2;
    lines[6][1] = 6;
    lines[7][0] = 3;
    lines[7][1] = 7;

    lines[8][0] = 4;
    lines[8][1] = 5;
    lines[9][0] = 4;
    lines[9][1] = 6;
    lines[10][0] = 5;
    lines[10][1] = 7;
    lines[11][0] = 6;
    lines[11][1] = 7;

    Vec3 rotation = NewVec3(0, 0.005, 0);

    while (running){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            running = 0;
                            break;
                    }
            }
        }

        for (int i=0; i<n_points; i++){
            points[i] = RotatePoint(points[i], rotation);
        }

        DrawFrame(renderer, points, lines, n_points, n_lines);
    }

    return 0;
}

int main(){
    printf("initializing SDL...");
    if (init()){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
        return -1;
    }
    printf("done\n");

    printf("start\n");
    mainloop(screen, renderer);

    Quit();
    return 0;
}