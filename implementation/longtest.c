#include <stdio.h>
#include <math.h>
extern double my_sinh(double x);
double abs(double x) {
	if (x < 0) {return -x;}
	return x;
}

int main() {
    double d = 0;
    double maxDiviation = 0;
    double maxErrorD = 0;
    int i = 0;
    do {
        double ms = my_sinh(d);
        double s = sinh(d);
	double diviation = abs(1-ms/s);
        if (diviation > maxDiviation) {
		maxDiviation = diviation;
		maxErrorD = d;
	}
        if (i % 1000000 == 0) {
            i = 0;
            printf("d: %f my_sinh: %9.4e sinh: %9.4e delta: %9.4e\n", d, ms, s, ms/s - 1);
        }
        i += 1;
        d += 0.00001;
    } while (d <= 710);
    printf("d: %f diviation: %f", maxErrorD, maxDiviation);
    return 0;
}
