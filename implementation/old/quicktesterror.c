/*Standard libraries that are required for math, output, etc.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

/*The assembly program that will be tested and compared against the standard library function*/
//extern double era_sinh(double x);

/*The function that will be called to compare assembly and standard programs, which will also write the result in a .csv file*/
void errorTestCase(double tmp, double *worstError, double *index, FILE *fp);

int main() {
    /*The variables are, in order, worst error, the index of the worst error, a temporary
    variable for test cases generated from the variable; such as i, i +- epsilon. */
    double worstError = 0, index, tmp;

    /* Creating the output file */
    FILE *fp;
    fp = createFile("Quick_Test_Error_");

    /*This is the top row of our csv file which will record all tests according to the used
    program's specifications (speed only records speed, error only records error, both records
    both speed and error for standard library and our assembly program's results)*/
    fprintf(fp, "Test Var,Our Output,Std Output,The Deviation Was\n");
    
    /* Critical values are tested here. There are a total of 1420 * 4 * 3 = 17040 */
    for (double i = -711; i < 711; i += 0.25) {

	/* tmp is used to hold the values that are right next to i, without disrupting the
        for loop */
	/* testing for critical value i */
        tmp = i;
        errorTestCase(tmp, &worstError, &index, fp);
	
        /* critical value i + epsilon */
        tmp = nextafter(i, 712);
        errorTestCase(tmp, &worstError, &index, fp);

        /* critical value i - epsilon */
        tmp = nextafter(i, -712);
        errorTestCase(tmp, &worstError, &index, fp);
    }

    /* 1500 random values between 0 and 712 are tested here */
    for (int i = 0; i < 1500; i++) {
        tmp = (double)rand()/(double)(RAND_MAX/712);
        errorTestCase(tmp, &worstError, &index, fp);
    }

    /* 1500 random values between -712 and 0 are tested here */
    for (int i = 0; i < 1500; i++) {
        tmp = (double)rand()/(double)(RAND_MAX/712);
        tmp = -tmp;
        errorTestCase(tmp, &worstError, &index, fp);
    }

    /* The file is closed to avoid leaks and to make sure the whole stream is written */
    fclose(fp);

    /* The worst error rate and its index is displayed on the console */
    printf("Worst error is %e at %e\n", worstError, index);
}

void errorTestCase(double tmp, double *worstError, double *index, FILE *fp) {
    /* first we calculate the result for our function */
    double ourResult = era_sinh(tmp);
    /* then we calculate the result for the standard function */
    double stdResult = sinh(tmp);
    /* the error rate is our result divided by the standard result */
    double currError = 1 - (ourResult / stdResult);
    /* a comparison is made to see if the current error is so far the worst one */
    if (currError > *worstError) {
        /* if it is the worst case so far, the worst error and the index is updated */
        *worstError = currError;
	*index = tmp;
    }
        /* the result of each test is written in the previously created file */
        fprintf(fp, "%.17g,%e,%e,%e\n", tmp, ourResult, stdResult, currError);
}
