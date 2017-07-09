/*Standard libraries that are required for math, output, time, etc.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "functions.h"

/*The assembly program that will be tested and compared against the standard library function*/
//extern double era_sinh(double x);

/*double era_sinh(double x) {
    extern double era_sinh(double x);
}*/

/*This block is for creating a file with an appropriate name. The name of the test and the
current time stamp is used to create a unique and easy to understand file identifier.*/
FILE* createFile(char *input) {
    /*First, we create a time stamp*/
    struct tm *gtime;
    time_t now;
    time(&now);
    char fstamp[24] = "";
    strftime(fstamp, sizeof(fstamp), "%Y-%m-%d_%H:%M:%S.csv", localtime(&now));
    /*Then, we create the file, and add the stamp at the end*/
    FILE *fp;
    char fname[200] = "./";
    strcat(fname, input);
    strcat(fname, fstamp);
    fp = fopen(fname,"w");
    return fp;
}
    /* END OF BLOCK */

/*The function that will be called to measure the length and the result of sinh(x) written for ERA*/
double ourDuration(double x, double* y) {
    clock_t start = clock();
    *y = era_sinh(x);
    clock_t stop = clock();
    return (double)(stop - start) / CLOCKS_PER_SEC * 1000;
}

/*The function that will be called to measure the length and the result of sinh(x) of standard library*/
double stdDuration(double x, double* y) {
    clock_t start = clock();
    *y = sinh(x);
    clock_t stop = clock();
    return (double)(stop - start) / CLOCKS_PER_SEC * 1000;
}


/* A standard test case that is used by all tests that record both error and speed */
void testCase(double tmp, double *worstSpeed, double *indexSpeed, double *worstError, double *indexError, FILE *fp) {
    /* first we calculate the result for our function */
    double ourResult;
    double ourSpeed = ourDuration(tmp, &ourResult);
    /* then we calculate the result for the standard function */
    double stdResult;
    double stdSpeed = stdDuration(tmp, &stdResult);
    /* a comparison is made to see if the current speed difference is so far the worst one */
    if (ourSpeed - stdSpeed > *worstSpeed) {
        /* if it is the worst case so far, the worst speed and the index is updated */
        *worstSpeed = ourSpeed - stdSpeed;
        *indexSpeed = tmp;
    }
    /* the error rate is our result divided by the standard result */
    double currError = 1 - (ourResult / stdResult);
    /* a comparison is made to see if the current error is so far the worst one */
    if (currError > *worstError) {
        /* if it is the worst case so far, the worst error and the index is updated */
        *worstError = currError;
	*indexError = tmp;
    }
    /* the result of each test is written in the previously created file */
    fprintf(fp, "%.17g,%e,%e,%e,", tmp, ourResult, stdResult, currError);
    //fprintf(fp, "%e,%e,%e\n", ourSpeed, stdSpeed, (ourSpeed - stdSpeed));
}
