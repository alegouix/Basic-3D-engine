#include "draw.h"

void DrawFrame(SDL_Renderer* renderer, Point** points, int *lines[2], int n_points, int n_lines){
    Vec3 proj, projections[n_points];
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int i=0; i<n_points; i++){
        proj = GetProjection(points[i]);
        projections[i] = proj;
        DrawPoint(renderer, proj);
    }

    for (int i=0; i<n_lines; i++){
        SDL_RenderDrawLine(renderer, projections[lines[i][0]].x, projections[lines[i][0]].y, projections[lines[i][1]].x, projections[lines[i][1]].y);
    }

    SDL_RenderPresent(renderer);
}

void DrawPoint(SDL_Renderer* renderer, Vec3 pos){
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderDrawPoint(renderer, pos.x, pos.y);
    return;
}