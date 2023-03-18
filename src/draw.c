#include "draw.h"
#include "triangle.h"
#include "engine_defs.h"
#include "utils.h"

void DrawFrame(SDL_Renderer* renderer, int draw_mode, Triangle** triangles, Point** points, int *lines[2], int n_triangles, int n_points, int n_lines){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // printf("before %f\n", DEPTH_BUFFER[*WINDOW_WIDTH**WINDOW_HEIGHT/2]);
    // printf("after %f\n", DEPTH_BUFFER[*WINDOW_WIDTH**WINDOW_HEIGHT/2]);
    switch (draw_mode){
    case DRAWMODE_WIREFRAME:
        DrawWireFrame(renderer, points, lines, n_points, n_lines);
        break;
    
    case DRAWMODE_TRIANGLE:
        ResetDepthBuffer();//DEPTH_BUFFER = memset(DEPTH_BUFFER, 0, *WINDOW_WIDTH**WINDOW_HEIGHT);
        DrawTriangleFrame(renderer, triangles, n_triangles);
        break;

    case DRAWMODE_BOTH:
        ResetDepthBuffer();
        DrawTriangleFrame(renderer, triangles, n_triangles);
        DrawWireFrame(renderer, points, lines, n_points, n_lines);
        break;

    case DRAWMODE_DEPTH:
        DrawDepthBuffer(renderer);
        break;

    default:
        break;
    }


    /* debug */
    // SDL_Surface* surf = triangles[0]->texture;
    // Uint8 r, g, b;
    // for (int x=0; x<surf->w; x++){
    //     for (int y=0; y<surf->h; y++){
    //         SDL_GetRGB(getpixel(surf, x, y), surf->format, &r, &g, &b);
    //         SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    //         SDL_RenderDrawPoint(renderer, x, y);
    //     }
    // }
    // SDL_Rect re = {surf->w, 0, surf->w, surf->h};
    // SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, surf), NULL, &re);

    SDL_RenderPresent(renderer);
}

double get_triangle_dist(Triangle* t){
    double avg = (t->draw_points[2]->position.z + t->draw_points[1]->position.z + t->draw_points[0]->position.z) / 3;
    return avg;
}

/* the points of a triangle after projection and rotation */
int needs_draw(Triangle* t){
    Vec3 points[3];
    points[0] = RotatePoint(t->points[0], *ROTATION)->position;
    points[1] = RotatePoint(t->points[1], *ROTATION)->position;
    points[2] = RotatePoint(t->points[2], *ROTATION)->position;
    double a = DotProduct(TNormal(points), Vec3SubVec3(NewVec3(0, 0, -*Z0), points[0]));

    // printf("--------------------\n");
    // Vec3 v = TNormal(points);
    // printf("%f, %f, %f\n", v.x, v.y, v.z);
    // v = Vec3MultScalar(points[0], -1);
    // printf("%f, %f, %f\n", v.x, v.y, v.z);
    // printf("%.7f\n", a);
    return a > 0.0000001;
}

void DrawTriangleFrame(SDL_Renderer* renderer, Triangle** triangles, int n_triangles){
    Vec3 proj, projections[3];
    // sort_triangles(&triangles, n_triangles);
    for (int i=0; i<n_triangles; i++){
        if (!needs_draw(triangles[i])){continue;}
        for (int j=0; j<3; j++){
            // triangles[i]->points[j]->position.z += 100;
            proj = GetProjection(triangles[i]->points[j]);
            // triangles[i]->points[j]->position.z -= 100;
            projections[j] = proj;
            triangles[i]->draw_points[j] = NewPoint(proj.x, proj.y, proj.z);
            // printf("%lf, %lf, %lf\n", proj.x, proj.y, proj.z);
        }

        DrawTexturedTriangle(renderer, triangles[i]->texture, projections[0], projections[1], projections[2], triangles[i]->uv);

        /*draw normal vector for debug*/
        // Vec3 v = TNormal(projections);
        // int x = projections[0].x + 100* v.x;
        // int y = projections[0].y + 100* v.y;
        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        // SDL_RenderDrawLine(renderer, projections[0].x, projections[0].y, x, y);
    }
}

void DrawWireFrame(SDL_Renderer* renderer, Point** points, int *lines[2], int n_points, int n_lines){
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    Vec3 proj, projections[n_points];
    for (int i=0; i<n_points; i++){
        proj = GetProjection(points[i]);
        projections[i] = proj;
        // DrawPoint(renderer, proj);
    }

    for (int i=0; i<n_lines; i++){
        SDL_RenderDrawLine(renderer, projections[lines[i][0]].x, projections[lines[i][0]].y, projections[lines[i][1]].x, projections[lines[i][1]].y);
    }
}

void DrawPoint(SDL_Renderer* renderer, Vec3 pos){
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderDrawPoint(renderer, pos.x, pos.y);
    return;
}



void sort_triangles(Triangle*** triangles, int n_triangles){
    Triangle* temp;
    double d1, d2;
    for (int i=0; i<n_triangles; i++){
        for (int j=i+1; j<n_triangles; j++){
            d1 = get_triangle_dist((*triangles)[i]);
            d2 = get_triangle_dist((*triangles)[j]);
            if (d2 > d1){
                temp = (*triangles)[i];
                (*triangles)[i] = (*triangles)[j];
                (*triangles)[j] = temp;
            }
        }
    }
}


/* https://www.gabrielgambetta.com/computer-graphics-from-scratch/07-filled-triangles.html */
double* Interpolate (double i0, double d0, double i1, double d1) {
    // int s = fmax(1, (int)(i1-i0));
    double s = (i1-i0);
    double *values = (double*)calloc(s, sizeof(double));
    double a;
    a = (d1 - d0) / (double)s;
    // printf("%lf, %lf\n", i1, i0);
    double d = d0;

    for (int i=0; i<s; i++){
        values[i] = d;
        d = d + a;
    }
    // printf("%d, %f\n", s, values[20]);
    return values;
}

void swap(void * a, void * b, size_t len){
    unsigned char * p = a, * q = b, tmp;
    for (size_t i = 0; i != len; ++i)
    {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}
int DrawFilledTriangle (SDL_Renderer* renderer, Vec3 P0, Vec3 P1, Vec3 P2, char color[3]) {
   // Sort the points so that y0 <= y1 <= y2
   P0 = Vec3Round(P0);
   P1 = Vec3Round(P1);
   P2 = Vec3Round(P2);
    if (P1.y < P0.y){swap(&P1, &P0, sizeof(Vec3));}
    if (P2.y < P0.y){swap(&P2, &P0, sizeof(Vec3));}
    if (P2.y < P1.y){swap(&P2, &P1, sizeof(Vec3));}

   // Compute the x coordinates of the triangle edges
    double *x01 = Interpolate(P0.y, P0.x, P1.y, P1.x);
    double *x12 = Interpolate(P1.y, P1.x, P2.y, P2.x);
    double *x02 = Interpolate(P0.y, P0.x, P2.y, P2.x);
    // for (int i=0; i<P1.y; i++){
    //     printf("%d : %f\n", i, x01[i]);
    // }

    // Concatenate the short sides
    int s1 = fmax(1, P1.y-P0.y);
    // int s2 = fmax(1, P2.y-P1.y);
    int s3 = fmax(1, P2.y-P0.y);
    // int len = s1 + s2;
    // double* x012 = (double*)calloc(len, sizeof(double));
    // for (int i=0; i<s1; i++){
    //     x012[i] = x01[i];
    // }
    // for (int i=0; i<s2; i++){
    //     x012[i+s1] = x12[i];
    // }

    double z, zr, zl;
    double *short_segment = x01;
    int ind=0, s=0;

    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
   // Draw the horizontal segments
    for (int y=1; y<s3-1; y++){
        // printf("the y is %d\n", y);

        if (y == s1){
            short_segment = x12;
            ind = y;
            s = 1;
        }

        if (y < 0 || y >= *WINDOW_HEIGHT){continue;}

        // SDL_RenderDrawLine(renderer, x_left[y], P0.y+y, x_right[y], P0.y+y);
        zr = lerp(P0.z, P2.z, (double)y/(double)s3);
        if (s){
            zl = lerp(P0.z, P1.z, (double)y/(double)s3);
        }
        else{
            zl = lerp(P1.z, P2.z, (double)y/(double)s3);
        }
        // printf("step %d / %d\n", y, s3);
        // printf("P012.z : %f, %f, %f\n", P0.z, P1.z, P2.z);
        // printf("zl = %f, zr = %f\n", zl, zr);
        if (x02[y] > short_segment[y-ind]){
            for (int x=short_segment[y-ind]; x<x02[y]; x++){
                if (x < 0 || x > *WINDOW_WIDTH){continue;}
                z = lerp(zr, zl, (double)(x-x02[y])/(short_segment[y-ind]-x02[y]));
                // printf("%f\n", z);
                if (z < DEPTH_BUFFER[((int)P0.y+y)**WINDOW_WIDTH + x]){
                    SDL_RenderDrawPoint(renderer, x, P0.y+y);
                    DEPTH_BUFFER[((int)P0.y+y)**WINDOW_WIDTH + x] = z;
                    if (z > *MAX_DEPTH){
                        *MAX_DEPTH = z;
                    }
                    if (z < *MIN_DEPTH){
                        *MIN_DEPTH = z;
                    }
                }
            }
        }
        else{
            for (int x=x02[y]; x<short_segment[y-ind]; x++){
                // printf("%d\n", x);
                if (x02[y] > short_segment[y-ind]){break;}
                if (x < 0 || x >= *WINDOW_WIDTH){continue;}
                z = lerp(zr, zl, (double)(x-x02[y])/(short_segment[y-ind]-x02[y]));
                // if ((double)(x-x02[y])/(short_segment[y-ind]-x02[y]) > 1){
                //     printf("line %d, x = %d\n", y, x);
                //     printf("%f\n", (double)(x-x02[y])/(double)(short_segment[y-ind]-x02[y]));
                //     printf("%f, %f\n", x02[y], short_segment[y-ind]);
                // }
                if (z < DEPTH_BUFFER[((int)P0.y+y)**WINDOW_WIDTH + x]){
                    SDL_SetRenderDrawColor(renderer,color[0], color[1], color[2], 255);
                    SDL_RenderDrawPoint(renderer, x, P0.y+y);
                    DEPTH_BUFFER[((int)P0.y+y)**WINDOW_WIDTH + x] = z;
                    if (z > *MAX_DEPTH){
                        *MAX_DEPTH = z;
                    }
                    if (z < *MIN_DEPTH){
                        *MIN_DEPTH = z;
                    }
                }
            }
        }
    }
            // printf("%f\n", DEPTH_BUFFER[y**WINDOW_WIDTH + x]);

    return 0;
}

int DrawTexturedTriangle (SDL_Renderer* renderer, SDL_Surface* texture, Vec3 P0, Vec3 P1, Vec3 P2, Point2D* UV) {
   // Sort the points so that y0 <= y1 <= y2
   
    // int texture_width, texture_height;

    Point2D* uv = (Point2D*)calloc(3, sizeof(Point2D));
    memcpy(uv, UV, sizeof(Point2D)*3);

   P0 = Vec3Round(P0);
   P1 = Vec3Round(P1);
   P2 = Vec3Round(P2);
    if (P1.y < P0.y){swap(&P1, &P0, sizeof(Vec3)); swap(&uv[1], &uv[0], sizeof(Point2D));}
    if (P2.y < P0.y){swap(&P2, &P0, sizeof(Vec3)); swap(&uv[2], &uv[0], sizeof(Point2D));}
    if (P2.y < P1.y){swap(&P2, &P1, sizeof(Vec3)); swap(&uv[2], &uv[1], sizeof(Point2D));}

   // Compute the x coordinates of the triangle edges
    double *x01 = Interpolate(P0.y, P0.x, P1.y, P1.x);
    double *x12 = Interpolate(P1.y, P1.x, P2.y, P2.x);
    double *x02 = Interpolate(P0.y, P0.x, P2.y, P2.x);
    // for (int i=0; i<P1.y; i++){
    //     printf("%d : %f\n", i, x01[i]);
    // }

    // Concatenate the short sides
    int s1 = fmax(1, P1.y-P0.y);
    int s2 = fmax(1, P2.y-P1.y);
    int s3 = fmax(1, P2.y-P0.y);
    // int len = s1 + s2;
    // double* x012 = (double*)calloc(len, sizeof(double));
    // for (int i=0; i<s1; i++){
    //     x012[i] = x01[i];
    // }
    // for (int i=0; i<s2; i++){
    //     x012[i+s1] = x12[i];
    // }

    double z, zr, zl, pa, pb, dx;
    double *short_segment = x01;
    int ind=0, s=0; /* s is set to 1 when we switch between short segments */
    Uint8 r=0,g=0,b=0;
    Point2D pl, pr, p, p1, p2;

   // Draw the horizontal segments
    for (int y=1; y<s3-1; y++){
        // printf("the y is %d\n", y);

        if (y == s1){
            short_segment = x12;
            ind = y;
            s = 1;
        }

        if (y < 0 || y >= *WINDOW_HEIGHT){continue;}

        // SDL_RenderDrawLine(renderer, x_left[y], P0.y+y, x_right[y], P0.y+y);
        zr = lerp(P0.z, P2.z, (double)y/(double)s3);
        pr.x = lerp(uv[0].x, uv[2].x, (double)y/(double)s3);
        pr.y = lerp(uv[0].y, uv[2].y, (double)y/(double)s3);
        if (!s){
            // printf("%d\n", y);
            zl = lerp(P0.z, P1.z, (double)y/(double)s1);
            pl.x  = lerp(uv[0].x, uv[1].x, (double)y/(double)s1);
            pl.y  = lerp(uv[0].y, uv[1].y, (double)y/(double)s1);
        }
        else{
            zl = lerp(P1.z, P2.z, (double)(y-s1)/(double)s2);
            pl.x  = lerp(uv[1].x, uv[2].x, (double)(y-s1)/(double)s2);
            pl.y  = lerp(uv[1].y, uv[2].y, (double)(y-s1)/(double)s2);
        }
        // printf("step %d / %d\n", y, s3);
        // printf("P012.z : %f, %f, %f\n", P0.z, P1.z, P2.z);
        // printf("zl = %f, zr = %f\n", zl, zr);
        if (x02[y] > short_segment[y-ind]){
            swap(&pr, &pl, sizeof(Point2D));
            for (int x=ceil(short_segment[y-ind]); x<x02[y]; x++){
                if (x < 0 || x > *WINDOW_WIDTH || short_segment[y-ind] >= x02[y]){continue;}
                z = lerp(zr, zl, (double)(x-x02[y])/(short_segment[y-ind]-x02[y]));
                // printf("%p, %d\n", texture, px_index);
                // printf("%u\n", ((Uint32*)texture->pixels)[px_index]);
                if (z<0 || z < DEPTH_BUFFER[((int)P0.y+y)**WINDOW_WIDTH + x]){
                    dx = (x-ceil(short_segment[y-ind]))/(x02[y]-ceil(short_segment[y-ind]));

                    pa = (double)(y)/(s3-1); /*pos on 0-2 side*/
                    p1.x = lerp(uv[0].x, uv[2].x, pa);
                    p1.y = lerp(uv[0].y, uv[2].y, pa);


                    if (!s){
                        pb = (double)y / s1; /* pos on 0-1 side */
                        p2.x = lerp(uv[0].x, uv[1].x, pb);
                        p2.y = lerp(uv[0].y, uv[1].y, pb);
                    }else{
                        pb = (double)(y-ind) / s2; /* pos on 1-2 side */
                        p2.x = lerp(uv[1].x, uv[2].x, pb);
                        p2.y = lerp(uv[1].y, uv[2].y, pb);
                    }

                    p.x = texture->w * lerp(p2.x, p1.x, dx);
                    p.y = texture->h * lerp(p2.y, p1.y, dx);

                    // printf("%f, %f, %f\n", pa, pb, dx);
                    // printf("%f, %f\n", p.x, p.y);

                    SDL_GetRGB(getpixel(texture, p.x, p.y), texture->format, &r, &g, &b);
                    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                    SDL_RenderDrawPoint(renderer, x, P0.y+y);
                    DEPTH_BUFFER[((int)P0.y+y)**WINDOW_WIDTH + x] = z;
                    if (z > *MAX_DEPTH){
                        *MAX_DEPTH = z;
                    }
                    if (z < *MIN_DEPTH){
                        *MIN_DEPTH = z;
                    }
                }
                // printf("finish\n");
            }
        }
        else{
            for (int x=x02[y]; x<short_segment[y-ind]; x++){
                // printf("%d\n", x);
                if (x02[y] > short_segment[y-ind]){break;}
                if (x < 0 || x >= *WINDOW_WIDTH){continue;}
                z = lerp(zr, zl, (double)(x-x02[y])/(short_segment[y-ind]-x02[y]));
                // if ((double)(x-x02[y])/(short_segment[y-ind]-x02[y]) > 1){
                //     printf("line %d, x = %d\n", y, x);
                //     printf("%f\n", (double)(x-x02[y])/(double)(short_segment[y-ind]-x02[y]));
                //     printf("%f, %f\n", x02[y], short_segment[y-ind]);
                // }
                if (z < DEPTH_BUFFER[((int)P0.y+y)**WINDOW_WIDTH + x]){
                    dx = (x-ceil(short_segment[y-ind]))/(x02[y]-ceil(short_segment[y-ind]));

                    pa = (double)(y)/(s3-1); /*pos on 0-2 side*/
                    p1.x = lerp(uv[0].x, uv[2].x, pa);
                    p1.y = lerp(uv[0].y, uv[2].y, pa);


                    if (!s){
                        pb = (double)y / s1; /* pos on 0-1 side */
                        p2.x = lerp(uv[0].x, uv[1].x, pb);
                        p2.y = lerp(uv[0].y, uv[1].y, pb);
                    }else{
                        pb = (double)(y-ind) / s2; /* pos on 1-2 side */
                        p2.x = lerp(uv[1].x, uv[2].x, pb);
                        p2.y = lerp(uv[1].y, uv[2].y, pb);
                    }

                    p.x = texture->w * lerp(p2.x, p1.x, dx);
                    p.y = texture->h * lerp(p2.y, p1.y, dx);

                    SDL_GetRGB(getpixel(texture, p.x, p.y), texture->format, &r, &g, &b);
                    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                    SDL_RenderDrawPoint(renderer, x, P0.y+y);
                    DEPTH_BUFFER[((int)P0.y+y)**WINDOW_WIDTH + x] = z;
                    if (z > *MAX_DEPTH){
                        *MAX_DEPTH = z;
                    }
                    if (z < *MIN_DEPTH){
                        *MIN_DEPTH = z;
                    }
                }
            }
        }
    }
            // printf("%f\n", DEPTH_BUFFER[y**WINDOW_WIDTH + x]);

    // printf("%f / %d = %f\n", avg/(double)n, texture->h * texture->pitch, (avg/(double)n)/(double)(texture->h * texture->pitch));

    return 0;
}
void DrawDepthBuffer(SDL_Renderer* renderer){
    for (int x = 0; x<*WINDOW_WIDTH; x++){
        for (int y=0; y<*WINDOW_HEIGHT; y++){
            int c = fmax(0, fmin(255, 255*(DEPTH_BUFFER[y**WINDOW_WIDTH + x]) / (*MAX_DEPTH)));
            // printf("%d, %d, %d, %d, %f\n", x, y, y**WINDOW_WIDTH + x, c, DEPTH_BUFFER[y**WINDOW_WIDTH + x]);
            SDL_SetRenderDrawColor(renderer, c, c, c, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}