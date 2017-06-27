#include <stdio.h>
#include <stdlib.h>
#include <math.h>
extern double era_sinh(double x);
int main(int argc, char *argv[]) {
    //double d = atof(argv[1]);
    double d = -10.0;
    //int loops = 1;
    double ms, s;
    //do {
        //loops = 1;
        //do {
            ms = era_sinh(d);
            s = sinh(d);
            //printf("d: %f my_sinh: %9.4e sinh: %9.4e delta: %9.4e\n", d, ms, s, ms/s - 1);
            //loops++;
        //} while (ms != s && loops < 1);
        printf("{%f,%f},", d, ms);
    //} while (d <= 700);
    //printf("It took %d loops to make era_sinh as accurate as the build in one for %f\n", loops, d);
    return 0;
}
