#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
extern double era_sinh(double x);

double ourDuration(double x, double* y) {
    clock_t start = clock();
    *y = era_sinh(x);
    clock_t stop = clock();
    return (double)(stop - start) / CLOCKS_PER_SEC * 1000;
}

double stdDuration(double x, double* y) {
    clock_t start = clock();
    *y = sinh(x);
    clock_t stop = clock();
    return (double)(stop - start) / CLOCKS_PER_SEC * 1000;
}

int main() {
    double worstSpeed = 0, stdSpeed, ourSpeed, indexSpeed, tmp;
    double worstError = 0, currError, stdResult, ourResult, indexError;
    char fname[50];
    struct tm *gtime;
    time_t now;
    time(&now);
    strftime(fname, sizeof(fname), "./Quick_Test_Both_%Y-%m-%d_%H:%M:%S.csv", localtime(&now));
    FILE *fp;
    fp = fopen(fname,"w");
    fprintf(fp, "Test Var,Our Output,Std Output,The Deviation Was,");
    fprintf(fp, "Our Output (in ms),Std Output (in ms),We Took X Ms Longer\n");
    

    /* Error values are Nan, infinity, negative infinity, 720, -720, char (not a number)*/
    /* critical values are tested here
       710 * 4 * 3 = 8520 */
    for (double i = 0; i < 711; i += 0.25) {

        /* critical value i */
        ourSpeed = ourDuration(i, &ourResult);
        stdSpeed = stdDuration(i, &stdResult);
        if (ourSpeed - stdSpeed > worstSpeed) {
            worstSpeed = ourSpeed - stdSpeed;
	    indexSpeed = i;
        }
        currError = 1-ourResult/stdResult;
        if (currError > worstError) {
            worstError = currError;
	    indexError = i;
        }
        fprintf(fp, "%.17g,%e,%e,%e,", i, ourResult, stdResult, currError);
        fprintf(fp, "%e,%e,%e\n", ourSpeed, stdSpeed, (ourSpeed - stdSpeed));
        /* critical value i + epsilon */
        tmp = nextafter((double)i, (double)i+1);
        ourSpeed = ourDuration(tmp, &ourResult);
        stdSpeed = stdDuration(tmp, &stdResult);
        if (ourSpeed - stdSpeed > worstSpeed) {
            worstSpeed = ourSpeed - stdSpeed;
	    indexSpeed = tmp;
        }
        currError = 1-ourResult/stdResult;
        if (currError > worstError) {
            worstError = currError;
	    indexError = tmp;
        }
        fprintf(fp, "%.17g,%e,%e,%e,", tmp, ourResult, stdResult, currError);
        fprintf(fp, "%e,%e,%e\n", ourSpeed, stdSpeed, (ourSpeed - stdSpeed));
        /* critical value i - epsilon */
        tmp = nextafter((double)i, (double)i-1);
        ourSpeed = ourDuration(tmp, &ourResult);
        stdSpeed = stdDuration(tmp, &stdResult);
        if (ourSpeed - stdSpeed > worstSpeed) {
            worstSpeed = ourSpeed - stdSpeed;
	    indexSpeed = tmp;
        }
        currError = 1-ourResult/stdResult;
        if (currError > worstError) {
            worstError = currError;
	    indexError = tmp;
        }
        fprintf(fp, "%.17g,%e,%e,%e,", tmp, ourResult, stdResult, currError);
        fprintf(fp, "%e,%e,%e\n", ourSpeed, stdSpeed, (ourSpeed - stdSpeed));
    }
    /* 1500 random values between 0 and 710 are tested here */
    for (int i = 0; i < 1500; i++) {
	tmp = (double)rand()/(double)(RAND_MAX/710);
        ourSpeed = ourDuration(tmp, &ourResult);
        stdSpeed = stdDuration(tmp, &stdResult);
        if (ourSpeed - stdSpeed > worstSpeed) {
            worstSpeed = ourSpeed - stdSpeed;
	    indexSpeed = tmp;
        }
        currError = 1-ourResult/stdResult;
        if (currError > worstError) {
            worstError = currError;
	    indexError = tmp;
        }
        fprintf(fp, "%.17g,%e,%e,%e,", tmp, ourResult, stdResult, currError);
        fprintf(fp, "%e,%e,%e\n", ourSpeed, stdSpeed, (ourSpeed - stdSpeed));
    }
    fclose(fp);
    printf("Worst error is %e at %e\n", worstError, indexError);
    printf("Worst speed is %e at %e\n", worstSpeed, indexSpeed);
}
