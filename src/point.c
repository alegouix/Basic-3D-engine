#include <stdlib.h>
#include <stdio.h>
#include "engine_defs.h"
#include "point.h"

Point* RotatePoint(Point* p, Vec3 rotation){
    double x1, y1, z1, x2, y2, z2, rx, ry, rz;
    x1 = p->position.x;
    y1 = p->position.y;
    z1 = p->position.z;
    x2 = rotation.x;
    y2 = rotation.y;
    z2 = rotation.z;

    /* https://en.wikipedia.org/wiki/Rotation_matrix */
    rx = x1 * (cos(x2) * cos(y2)) +
         y1 * (cos(x2) * sin(y2) * sin(z2) - sin(x2)*cos(z2)) +
         z1 * (cos(x2) * sin(y2) * cos(x2) + sin(x2)*sin(z2));
    ry = x1 * (sin(x2) * cos(y2)) +
         y1 * (sin(x2) * sin(y2) * sin(z2) + cos(x2)*cos(z2)) +
         z1 * (sin(x2) * sin(y2) * cos(z2) + cos(x2)*sin(z2));
    // rz = x1 * (-sin(y2)) +
    //      y1 * (sin(x2) * cos(y2)) +
    //      z1 * (cos(x2) * cos(y2));
    rz = x1 * (-sin(y2)) +
         y1 * (cos(y2) * sin(z2)) +
         z1 * (cos(y2) * cos(z2));
        
    return NewPoint(rx, ry, rz);
}

Vec3 GetProjection(Point* point){
    double x, y, z, Z;
    // printf("br : %f, %f, %f\n", point->position.x, point->position.y, point->position.z);
    Point* p = RotatePoint(point, *ROTATION);
    // printf("ar : %f, %f, %f\n", p->position.x, p->position.y, p->position.z);
    x = p->position.x;
    y = p->position.y;
    z = p->position.z;
    Z = *Z0 / (*Z0 + z);

    return Vec3AddVec3(NewVec3(x*Z, y*Z, z), NewVec3(*WINDOW_WIDTH/2, *WINDOW_HEIGHT/2, 0));
}

Point* TranslatePoint(Point* p, Vec3 translation){
    Vec3 v = Vec3AddVec3(p->position, translation);
    return NewPoint(v.x, v.y, v.z);
}

Point* NewPoint(double x, double y, double z){
    Point* p = (Point*)malloc(sizeof(Point));

    p->position = NewVec3(x, y, z);

    return p;
}

void DelPoint(Point* p){
    free(p);
}