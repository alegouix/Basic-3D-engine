#include "engine.h"


SDL_Window* screen = NULL;
SDL_Renderer* renderer = NULL;

int init(){
    init_engine();
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        return -1;
    }

    if (!IMG_Init(IMG_INIT_JPG)){
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
    free(DEPTH_BUFFER);
}

int mainloop(SDL_Window* screen, SDL_Renderer* renderer){
    int running=1;
    SDL_Event event;


    int n_points;
    Point** points;
    int n_lines;
    int **lines;
    if(load_wireframe_model("models/cube.wire", &points, &lines, &n_points, &n_lines)){
    // if(load_wireframe_model("models/test_triangle", &points, &lines, &n_points, &n_lines)){
        return -1;
    }

    // for (int i=0; i<n_points; i++){
    //     points[i]->position.z += 500;
    // }


    int n_triangles = 12;
    Triangle** triangles = (Triangle**)calloc(n_triangles, sizeof(Triangle*));

    triangles[0] = NewTriangle(points[0], points[2], points[1], 1, 1, 1, 0, 0, 1);
    triangles[1] = NewTriangle(points[3], points[1], points[2], 0, 0, 0, 1, 1, 0);
    triangles[2] = NewTriangle(points[4], points[6], points[5], 0, 1, 1, 1, 0, 0);
    triangles[3] = NewTriangle(points[7], points[5], points[6], 1, 0, 0, 0, 1, 1);
    triangles[4] = NewTriangle(points[0], points[5], points[2], 0, 1, 1, 0, 0, 0);
    triangles[5] = NewTriangle(points[0], points[4], points[5], 0, 1, 1, 1, 1, 0);
    triangles[6] = NewTriangle(points[1], points[3], points[6], 1, 1, 1, 0, 0, 1);
    triangles[7] = NewTriangle(points[7], points[6], points[3], 0, 0, 0, 1, 1, 0);
    triangles[8] = NewTriangle(points[0], points[1], points[4], 1, 1, 1, 0, 0, 1);
    triangles[9] = NewTriangle(points[6], points[4], points[1], 0, 0, 0, 1, 1, 0);
    triangles[10] = NewTriangle(points[2], points[5], points[3], 1, 0, 0, 0, 1, 1);
    triangles[11] = NewTriangle(points[7], points[3], points[5], 0, 1, 1, 1, 0, 0);



    Vec3 rotation = NewVec3(0, 0.005, 0);
    int drawmode = DRAWMODE_TRIANGLE;

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
                        case SDLK_d:
                            if (drawmode == DRAWMODE_DEPTH){
                                drawmode = DRAWMODE_TRIANGLE;
                            }
                            else{
                                drawmode = DRAWMODE_DEPTH;
                            }
                    }
            }
        }

        *ROTATION = Vec3AddVec3(*ROTATION, rotation);
        if (ROTATION->x > 2*M_PI){
            ROTATION->x -= 2*M_PI;
        }
        else if (ROTATION->x > 2*M_PI){
            ROTATION->x -= 2*M_PI;
        }
        if (ROTATION->y > 2*M_PI){
            ROTATION->y -= 2*M_PI;
        }
        else if (ROTATION->y > 2*M_PI){
            ROTATION->y -= 2*M_PI;
        }
        if (ROTATION->z > 2*M_PI){
            ROTATION->z -= 2*M_PI;
        }
        else if (ROTATION->z > 2*M_PI){
            ROTATION->z -= 2*M_PI;
        }

        // printf("start DrawfFrame\n");
        DrawFrame(renderer, drawmode, triangles, points, lines, n_triangles, n_points, n_lines);
        // printf("end DrawfFrame\n");
    }

    // printf("esto finito pepito\n");
    return 0;
}

int main(){
    Triangle* t = NewTriangle(NewPoint(0, 0, 0), NewPoint(0, 1, 0), NewPoint(0, 0, 1), 0, 0, 0, 0, 0, 0);
    Vec3 n = TriangleNormal(t);
    printf("%f, %f, %f\n", n.x, n.y, n.z);
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