/*Standard libraries that are required for math, output, collecting time from pc, etc.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*The assembly program that will be tested and compared against the standard library function*/
extern double era_sinh(double x);

int main() {
    /*The variables are, in order, worst error, current error, standard result (from standard
    c library), our result, the index of the worst error, a temporary variable (which will
    be explained later). Current error is 1 - (our result divided by the standard result).*/
    double worstError = 0, currError, stdResult, ourResult, index, tmp;

    /*This block is for creating a file with an appropriate name. The name of the test and the
    current time stamp is used to create a unique and easy to understand file identifier.*/
    char fname[50];
    struct tm *gtime;
    time_t now;
    time(&now);
    strftime(fname, sizeof(fname), "./Quick_Test_Error_%Y-%m-%d_%H:%M:%S.csv", localtime(&now));
    FILE *fp;
    fp = fopen(fname,"w");
    /* END OF BLOCK */

    /*This is the top row of our csv file which will record all tests according to the used
    program's specifications (speed only records speed, error only records error, both records
    both speed and error for standard library and our assembly program's results)*/
    fprintf(fp, "Test Var,Our Output,Std Output,The Deviation Was\n");
    
    /* Critical values are tested here. There are a total of 1420 * 4 * 3 = 17040 */
    for (double i = -711; i < 711; i += 0.25) {

        /* critical value i */
        /* first we calculate the result for our function */
        ourResult = era_sinh(i);
        /* then we calculate the result for the standard function */
        stdResult = sinh(i);
        /* the error rate is our result divided by the standard result */
        currError = 1-ourResult/stdResult;
        /* a comparison is made to see if the current error is so far the worst one */
        if (currError > worstError) {
            /* if it is the worst case so far, the worst error and the index is updated */
            worstError = currError;
	    index = i;
        }
        /* the result of each test is written in the previously created file */
        fprintf(fp, "%.17g,%e,%e,%e\n", i, ourResult, stdResult, currError);

        /* critical value i + epsilon, same procedure as above */
        /* tmp is used to hold the values that are right next to i, without disrupting the
        for loop */
        tmp = nextafter((double)i, (double)i+1);
        ourResult = era_sinh(tmp);
        stdResult = sinh(tmp);
        currError = 1-ourResult/stdResult;
        if (currError > worstError) {
            worstError = currError;
	    index = tmp;
        }
        fprintf(fp, "%.17g,%e,%e,%e\n", tmp, ourResult, stdResult, currError);

        /* critical value i - epsilon, same procedure as above */
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
    /* 1500 random values between 0 and 710 are tested here, same procedure as above */
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
    /* The file is closed to avoid leaks and to make sure the whole stream is written */
    fclose(fp);
    /* The worst error rate and its index is displayed on the console */
    printf("Worst error is %e at %e\n", worstError, index);
}
