#include <stdio.h>
#include <stdlib.h>
#include <math.h>
extern double era_sinh(double x);
int main() {
    double d = -711;
    do {
        double ms = era_sinh(d);
        double s = sinh(d);
        printf("d: %f my_sinh: %9.4e sinh: %9.4e delta: %9.4e\n", d, ms, s, ms/s - 1);
        d += 1.0;
    } while (d <= 711.0);
    return 0;
}
