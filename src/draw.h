#include <SDL2/SDL.h>
#include "triangle.h"
#include "point.h"

int DrawFilledTriangle (SDL_Renderer* renderer, Vec3 P0, Vec3 P1, Vec3 P2, char color[3]);
void DrawFrame(SDL_Renderer* renderer, int draw_mode, Triangle** triangles, Point** points, int *lines[2], int n_triangles, int n_points, int n_lines);
void DrawTriangleFrame(SDL_Renderer* renderer, Triangle** triangles, int n_triangles);
void DrawTriangleNormals(SDL_Renderer* renderer, Triangle** triangles, int n_triangles);
void DrawWireFrame(SDL_Renderer* renderer, Point** points, int *lines[2], int n_points, int n_lines);
void DrawDepthBuffer(SDL_Renderer* renderer);
void DrawPoint(SDL_Renderer* renderer, Vec3 pos);

void sort_triangles(Triangle*** triangles, int n_triangles);