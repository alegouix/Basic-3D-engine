#ifndef _VEC
#define _VEC 1

typedef struct{
    double x, y, z;
} Vec3;

Vec3 NewVec3(double x, double y, double z);
Vec3 Vec3AddVec3(Vec3 a, Vec3 b);
Vec3 Vec3SubVec3(Vec3 a, Vec3 b);
Vec3 Vec3MultScalar(Vec3 a, double b);
double Vec3Dist(Vec3 a, Vec3 b);
double DotProduct(Vec3 a, Vec3 b);
double Vec3Norm(Vec3 a);
Vec3 Vec3Normalize(Vec3 v);
#endif