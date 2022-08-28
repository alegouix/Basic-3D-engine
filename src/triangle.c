#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "triangle.h"

/*wrong*/
Vec3 TriangleNormal(Triangle* t){
    Vec3 a = Vec3SubVec3(t->points[0]->position, t->points[1]->position);
    Vec3 b = Vec3SubVec3(t->points[0]->position, t->points[2]->position);
    Vec3 r = CrossProduct(a, b);

    r = Vec3MultScalar(r, 1/(sqrt(pow(Vec3Norm(a), 2) * pow(Vec3Norm(b), 2) - pow(DotProduct(a, b), 2))));

    return r;
}

Triangle* NewTriangle(Point* p1, Point* p2, Point* p3, char r, char g, char b){
    Triangle* t = (Triangle*)malloc(sizeof(Triangle));

    t->points[0] = p1;
    t->points[1] = p2;
    t->points[2] = p3;

    t->draw_points[0] = p1;
    t->draw_points[1] = p2;
    t->draw_points[2] = p3;

    t->color[0] = r;
    t->color[1] = g;
    t->color[2] = b;

    return t;
}

void DelTriangle(Triangle* t){
    DelPoint(t->points[0]);
    DelPoint(t->points[1]);
    DelPoint(t->points[2]);
    free(t);
}
