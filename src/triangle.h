#ifndef _TRI
#define _TRI

#include "point.h"

typedef struct{
    Point* points[3];
    Point* draw_points[3];
    char color[3];
}Triangle;

Vec3 TriangleNormal(Triangle* t);

Triangle* NewTriangle(Point* p1, Point* p2, Point* p3, char r, char g, char b);
void DelTriangle(Triangle* t);

#endif