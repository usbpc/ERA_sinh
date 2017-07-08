/*Standard libraries that are required for math, output, time, etc.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "functions.h"

/*The assembly program that will be tested and compared against the standard library function*/
extern double era_sinh(double x);

/*The function that will be called to compare assembly and standard programs, which will also write the result in a .csv file*/
void speedTestCase(double tmp, double *worstSpeed, double *index, FILE *fp);

int main() {
    /*The variables are, in order, worst speed, the index of the worst speed, a temporary
    variable for test cases generated from the variable; such as i, i +- epsilon. */
    double worstSpeed = 0, index, tmp;

    /* Creating the output file */
    FILE *fp;
    fp = createFile("Quick_Test_Speed_");

    /*This is the top row of our csv file which will record all tests according to the used
    program's specifications (speed only records speed, error only records error, both records
    both speed and error for standard library and our assembly program's results)*/
    fprintf(fp, "Test Var,Our Output (in ms),Std Output (in ms),We Took X Ms Longer\n");

    /* Critical values are tested here. There are a total of 1420 * 4 * 3 = 17040 */
    for (double i = -711; i < 711; i += 0.25) {

        /* tmp is used to hold the values that are right next to i, without disrupting the
        for loop */
        /* critical value i */
        tmp = i;
        speedTestCase(tmp, &worstSpeed, &index, fp);

        /* critical value i + epsilon */
        tmp = nextafter(i, 712);
        speedTestCase(tmp, &worstSpeed, &index, fp);

        /* critical value i - epsilon */
        tmp = nextafter(i, -712);
        speedTestCase(tmp, &worstSpeed, &index, fp);

    }

    /* 1500 random values between 0 and 712 are tested here */
    for (int i = 0; i < 1500; i++) {
        tmp = (double)rand()/(double)(RAND_MAX/712);
        speedTestCase(tmp, &worstSpeed, &index, fp);
    }

    /* 1500 random values between -712 and 0 are tested here */
    for (int i = 0; i < 1500; i++) {
        tmp = (double)rand()/(double)(RAND_MAX/712);
        tmp = -tmp;
        speedTestCase(tmp, &worstSpeed, &index, fp);
    }

    /* The file is closed to avoid leaks and to make sure the whole stream is written */
    fclose(fp);
    /* The worst speed difference and its index is displayed on the console */
    printf("Worst speed is %e at %e\n", worstSpeed, index);
}

/*The function that will be called to measure the length of sinh(x) written for ERA*/
double ourDuration_SpeedTest(double x) {
    clock_t start = clock();
    era_sinh(x);
    clock_t stop = clock();
    return (double)(stop - start) / CLOCKS_PER_SEC * 1000;
}

/*The function that will be called to measure the length of sinh(x) of standard library*/
double stdDuration_SpeedTest(double x) {
    clock_t start = clock();
    sinh(x);
    clock_t stop = clock();
    return (double)(stop - start) / CLOCKS_PER_SEC * 1000;
}

void speedTestCase(double tmp, double *worstSpeed, double *index, FILE *fp) {
    /* first we calculate the result for our function */
    double ourSpeed = ourDuration_SpeedTest(tmp);
    /* then we calculate the result for the standard function */
    double stdSpeed = stdDuration_SpeedTest(tmp);
    /* a comparison is made to see if the current speed difference is so far the worst one */
    if (ourSpeed - stdSpeed > *worstSpeed) {
        /* if it is the worst case so far, the worst speed and the index is updated */
        *worstSpeed = ourSpeed - stdSpeed;
	*index = tmp;
    }
    /* the result of each test is written in the previously created file */
    fprintf(fp, "%.17g,%e,%e,%e\n", tmp, ourSpeed, stdSpeed, ourSpeed - stdSpeed);
}
