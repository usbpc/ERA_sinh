#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
extern double era_sinh(double x);

int main() {
    double worstError = 0, currError, stdResult, ourResult, index, tmp;
    //currError is 1-ourResult/stdResult
    char fname[50];
    struct tm *gtime;
    time_t now;
    time(&now);
    strftime(fname, sizeof(fname), "./Quick_Test_Error_%Y-%m-%d_%H:%M:%S.csv", localtime(&now));
    FILE *fp;
    fp = fopen(fname,"w");
    fprintf(fp, "Test Var,Our Output,Std Output,The Deviation Was\n");
    

    /* Error values are Nan, infinity, negative infinity, 720, -720, char (not a number)*/
    /* critical values are tested here
       710 * 4 * 3 = 8520 */
    for (double i = 0; i < 711; i += 0.25) {

        /* critical value i */
        ourResult = era_sinh(i);
        stdResult = sinh(i);
        currError = 1-ourResult/stdResult;
        if (currError > worstError) {
            worstError = currError;
	    index = i;
        }
        fprintf(fp, "%.17g,%e,%e,%e\n", i, ourResult, stdResult, currError);
        /* critical value i + epsilon */
        tmp = nextafter((double)i, (double)i+1);
        ourResult = era_sinh(tmp);
        stdResult = sinh(tmp);
        currError = 1-ourResult/stdResult;
        if (currError > worstError) {
            worstError = currError;
	    index = tmp;
        }
        fprintf(fp, "%.17g,%e,%e,%e\n", tmp, ourResult, stdResult, currError);
        /* critical value i - epsilon */
        tmp = nextafter((double)i, (double)i-1);
        ourResult = era_sinh(tmp);
        stdResult = sinh(tmp);
        currError = 1-ourResult/stdResult;
        if (currError > worstError) {
            worstError = currError;
	    index = tmp;
        }
        fprintf(fp, "%.17g,%e,%e,%e\n", tmp, ourResult, stdResult, currError);
    }
    /* 1500 random values between 0 and 710 are tested here */
    for (int i = 0; i < 1500; i++) {
	tmp = (double)rand()/(double)(RAND_MAX/710);
        ourResult = era_sinh(tmp);
        stdResult = sinh(tmp);
        currError = 1-ourResult/stdResult;
        if (currError > worstError) {
            worstError = currError;
	    index = tmp;
        }
        fprintf(fp, "%.17g,%e,%e,%e\n", tmp, ourResult, stdResult, currError);
    }
    fclose(fp);
    printf("Worst error is %e at %e\n", worstError, index);
}
