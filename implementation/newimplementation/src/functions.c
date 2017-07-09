#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/*This function expects a string to output before requesting a double from stdin
 *and returns the double it gets.
 */
double readDoubleFromSTDIN(const char* input) {
	double read;
	printf("%s", input);
	scanf("%lf", &read);
	return read;
}

/*This block is for creating a file with an appropriate name. The name of the test and the
 *current time stamp is used to create a unique and easy to understand file identifier.
 */
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

/*Very simple function to clear the screen*/
void clearScreen() {
	printf("\x1b[2J\x1b[1;1H");
}