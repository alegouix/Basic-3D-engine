#include <SDL2/SDL.h>
#include "point.h"

void DrawFrame(SDL_Renderer* renderer, Point** points, int *lines[2], int n_points, int n_lines);
void DrawPoint(SDL_Renderer* renderer, Vec3 pos);