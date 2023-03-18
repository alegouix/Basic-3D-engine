#ifndef _TRI
#define _TRI

#include <SDL2/SDL.h>
#include "point.h"
#include "utils.h"

typedef struct{
    Point* points[3];
    Point* draw_points[3];
    char color[3];
    Point2D uv[3];
    SDL_Surface* texture;
}Triangle;

Vec3 TriangleNormal(Triangle* t);
Vec3 TNormal(Vec3 points[3]);

Triangle* NewTriangle(Point* p1, Point* p2, Point* p3, double u0, double v0, double u1, double v1, double u2, double v2);
void DelTriangle(Triangle* t);

#endif