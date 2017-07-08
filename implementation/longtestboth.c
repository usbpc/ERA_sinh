/*Standard libraries that are required for math, output, etc.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

/*The assembly program that will be tested and compared against the standard library function*/
//extern double era_sinh(double x);

int main() {
    /*The variables are, in order, worst speed, the index of the worst speed, worst error, the 
    index of the worst error, a temporary variable for test cases generated from the variable;
    such as i, i +- epsilon. */
    double worstSpeed = 0, indexSpeed, worstError = 0, indexError, tmp;

    /* Creating the output file */
    FILE *fp;
    fp = createFile("Long_Test_Both_");

    /*This is the top row of our csv file which will record all tests according to the used
    program's specifications (speed only records speed, error only records error, both records
    both speed and error for standard library and our assembly program's results)*/
    fprintf(fp, "Test Var,Our Output,Std Output,The Deviation Was,");
    fprintf(fp, "Our Output (in ms),Std Output (in ms),We Took X Ms Longer\n");

    /* All values between -710 and 710 that are representable in a 64-bit float are tested*/
    for (double i = -710; i <= 710; nextafter((double)i, 712)) {
        testCase(i, &worstSpeed, &indexSpeed, &worstError, &indexError, fp);
    }
    /* The file is closed to avoid leaks and to make sure the whole stream is written */
    fclose(fp);
    /* The worst error rate and its index is displayed on the console */
    printf("Worst error is %e at %e\n", worstError, indexError);
    /* The worst speed difference and its index is displayed on the console */
    printf("Worst speed is %e at %e\n", worstSpeed, indexSpeed);
}
