#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "triangle.h"
#include "engine_defs.h"

Vec3 TriangleNormal(Triangle* t){
    Vec3 a = Vec3SubVec3(t->points[1]->position, t->points[0]->position);
    Vec3 b = Vec3SubVec3(t->points[2]->position, t->points[0]->position);
    // printf("%f, %f, %f\n", a.x, a.y, a.z);
    // printf("%f, %f, %f\n", b.x, b.y, b.z);
    Vec3 r = CrossProduct(a, b);

    r = Vec3MultScalar(r, 1/(sqrt(pow(Vec3Norm(a), 2) * pow(Vec3Norm(b), 2) - pow(DotProduct(a, b), 2))));

    return r;
}

Vec3 TNormal(Vec3 points[3]){
    Vec3 a = Vec3SubVec3(points[1], points[0]);
    Vec3 b = Vec3SubVec3(points[2], points[0]);
    // printf("%f, %f, %f\n", a.x, a.y, a.z);
    // printf("%f, %f, %f\n", b.x, b.y, b.z);
    Vec3 r = CrossProduct(a, b);

    r = Vec3MultScalar(r, 1/(sqrt(pow(Vec3Norm(a), 2) * pow(Vec3Norm(b), 2) - pow(DotProduct(a, b), 2))));

    return r;
}

Triangle* NewTriangle(Point* p1, Point* p2, Point* p3, double u0, double v0, double u1, double v1, double u2, double v2){
    Triangle* t = (Triangle*)malloc(sizeof(Triangle));

    t->points[0] = p1;
    t->points[1] = p2;
    t->points[2] = p3;

    t->draw_points[0] = p1;
    t->draw_points[1] = p2;
    t->draw_points[2] = p3;

    t->uv[0].x = u0;
    t->uv[0].y = v0;
    t->uv[1].x = u1;
    t->uv[1].y = v1;
    t->uv[2].x = u2;
    t->uv[2].y = v2;

    t->texture = CRATE_TEXTURE;

    return t;
}

void DelTriangle(Triangle* t){
    DelPoint(t->points[0]);
    DelPoint(t->points[1]);
    DelPoint(t->points[2]);
    free(t);
}
