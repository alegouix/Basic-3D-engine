#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "model.h"
#include "point.h"

int read_number(char* line, int i, double *res){
    double n = 0;
    int f = 0, k=0, run=1, neg=0;
    while (run){
        switch (line[i]){
        case 48: //0
            if (f){
                k ++;
                n += 0.0 * pow(10.0, -k);
            }
            else{
                n = n*10 + 0;
            }
            break;
        case 49: //1
            if (f){
                k ++;
                n += 1.0 * pow(10.0, -k);
            }
            else{
                n = n*10 + 1;
            }
            break;
        case 50: //2
            if (f){
                k ++;
                n += 2.0 * pow(10.0, -k);
            }
            else{
                n = n*10 + 2;
            }
            break;
        case 51: //3
            if (f){
                k ++;
                n += 3.0 * pow(10.0, -k);
            }
            else{
                n = n*10 + 3;
            }
            break;
        case 52: //4
            if (f){
                k ++;
                n += 4.0 * pow(10.0, -k);
            }
            else{
                n = n*10 + 4;
            }
            break;
        case 53: //5
            if (f){
                k ++;
                n += 5.0 * pow(10.0, -k);
            }
            else{
                n = n*10 + 5;
            }
            break;
        case 54: //6
            if (f){
                k ++;
                n += 6.0 * pow(10.0, -k);
            }
            else{
                n = n*10 + 6;
            }
            break;
        case 55: //7
            if (f){
                k ++;
                n += 7.0 * pow(10.0, -k);
            }
            else{
                n = n*10 + 7;
            }
            break;
        case 56: //8
            if (f){
                k ++;
                n += 8.0 * pow(10.0, -k);
            }
            else{
                n = n*10 + 8;
            }
            break;
        case 57: //9
            if (f){
                k ++;
                n += 9.0 * pow(10.0, -k);
            }
            else{
                n = n*10 + 9;
            }
            break;

        case 45: // -
            if (n == 0.){
                neg = 1;
            }
            else{
                run = 0;
            }
            break;

        case 46: // .
            if (1){
                run = 0;
                break;
            }
            else{
                f = 1;
                break;
            }

        default:
            run=0;
            break;
        }

        i ++;
    }

    *res = ((-neg)*2 + 1) * n;
    return i;
}

int load_wireframe_model(char* filename, Point*** points, int*** lines, int* n_points, int* n_lines){
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("ERROR %d could not open %s\n", errno, filename);
        return -1;
    }

    char line[100];

    double x, y, z, a, b;

    // char type;
    int np=0, nl=0, i;
    *points = (Point**)malloc(sizeof(Point*)*0);
    *lines = (int**)malloc(sizeof(int*)*0);
    // printf("%p, %p\n", *points, *lines);
    while (fgets(line, 100, file) != NULL){
        switch (line[0]){
        case 112: //p
            np ++;
            // printf("sizeof *points is %d\n", np);
            *points = (Point**)reallocarray(*points, 100, sizeof(Point*));
            if (*points == NULL){
                printf("ERROR %d at reallocarray\n", errno);
                return -1;
            }
            i = read_number(line, 1, &x);
            // printf("%f, %d\n", x, i);
            i = read_number(line, i, &y);
            // printf("%f, %d\n", y, i);
            i = read_number(line, i, &z);
            // printf("%f, %d\n", z, i);
            // printf("%p\n", *points);
            // printf("%d\n", np-1);
            // printf("%p\n", (*points)[0]);
            // printf("%p\n", (*points)[1]);
            (*points)[np-1] = NULL;            
            (*points)[np-1] = NewPoint(x, y, z);            
            break;
        
        case 108: //l
            // printf("%s", line);
            nl ++;
            *lines = (int**)reallocarray(*lines, nl, sizeof(int*));
            if (*lines == NULL){
                printf("ERROR %d at reallocarray\n", errno);
                return -1;
            }
            i = read_number(line, 1, &a);
            i = read_number(line, i, &b);
            // printf("%d, %d\n", (int)a, (int)b);
            (*lines)[nl-1] = (int*)calloc(2, sizeof(int));
            (*lines)[nl-1][0] = (int)a;
            (*lines)[nl-1][1] = (int)b;
            break;

        default:
            break;
        }
    }

    *n_points = np;
    *n_lines = nl;
    return 0;
}