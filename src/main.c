#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "engine_defs.h"
#include "draw.h"
#include "model.h"
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


    int n_points;
    Point** points;
    int n_lines;
    int **lines;

    if(load_wireframe_model("models/model.wire", &points, &lines, &n_points, &n_lines)){
        return -1;
    }

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