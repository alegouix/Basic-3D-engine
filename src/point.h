#ifndef _POINT
#define _POINT

#include "vector.h"

typedef struct{
    Vec3 position;
}Point;


Point* RotatePoint(Point* p, Vec3 rotation);
Vec3 GetProjection(Point* p);

Point* NewPoint(double x, double y, double z);
void DelPoint(Point* p);

#endif