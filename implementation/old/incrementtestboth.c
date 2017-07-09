/*Standard libraries that are required for math, output, etc.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

/*The assembly program that will be tested and compared against the standard library function*/
extern double era_sinh(double x);

int main() {
    /*The variables are, in order, worst speed, the index of the worst speed, worst error, the 
    index of the worst error, a temporary variable for test cases generated from the variable;
    such as i, i +- epsilon. */
    double worstSpeed = 0, indexSpeed, worstError = 0, indexError, tmp;

    /* Creating the output file */
    FILE *fp;
    fp = createFile("Increment_Test_Both_");

    /*This is the top row of our csv file which will record all tests according to the used
    program's specifications (speed only records speed, error only records error, both records
    both speed and error for standard library and our assembly program's results)*/
    fprintf(fp, "Test Var,Our Output,Std Output,The Deviation Was,");
    fprintf(fp, "Our Output (in ms),Std Output (in ms),We Took X Ms Longer\n");
    
    /*Default value of increment is 0.001. It is checked whether a valid increment is given.*/
    double j = 0.001;
    /*if argv[1].isDouble => j = argv[1]*/

    /*i is incremented by j until 710 and each value of i is tested*/
    for (double i = -710; i <= 710; i += j) {
        testCase(i, &worstSpeed, &indexSpeed, &worstError, &indexError, fp);
    }
    /* The file is closed to avoid leaks and to make sure the whole stream is written */
    fclose(fp);
    /* The worst error rate and its index is displayed on the console */
    printf("Worst error is %e at %e\n", worstError, indexError);
    /* The worst speed difference and its index is displayed on the console */
    printf("Worst speed is %e at %e\n", worstSpeed, indexSpeed);
}
