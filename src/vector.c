#include <math.h>
#include "vector.h"

extern Vec3 camera_pos;

Vec3 NewVec3(double x, double y, double z){
    Vec3 c = {x, y, z};
    return c;
}

Vec3 Vec3AddVec3(Vec3 a, Vec3 b){
    Vec3 c = {a.x + b.x, a.y + b.y, a.z + b.z};
    return c;
}

Vec3 Vec3SubVec3(Vec3 a, Vec3 b){
    Vec3 c = {a.x - b.x, a.y - b.y, a.z - b.z};
    return c;
}

Vec3 Vec3MultScalar(Vec3 a, double b){
    Vec3 c = {a.x * b, a.y * b, a.z * b};
    return c;
}

double DotProduct(Vec3 a, Vec3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double Vec3Dist(Vec3 a, Vec3 b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}
double Vec3Norm(Vec3 a){
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

Vec3 Vec3Normalize(Vec3 v){
    double norm = Vec3Norm(v);
    Vec3 u = NewVec3(v.x / norm, v.y / norm, v.z / norm);
    return u;
}