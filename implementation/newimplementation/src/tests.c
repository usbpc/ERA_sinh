#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "functions.h"
#include "sinh.h"

/*This tests all the numbers from from to to in steps of step and writes the results into fp.
 *it also prints the number with the worst deviation from the build in c function to stdout.
 */
void testValuesInRange(double from, double to, double step, FILE *fp) {
	//Used to save the results of our function and the C function.
	double sinhera = era_sinh(from), sinhc = sinh(from);
	//Used to remember the values where the worst deviation orrured.
	double worstera = 0, worstc = 0, worstInput = 0;
	//Used to save the relative error we had there from the C function
	double worstDeviation = 0;
	//Write the first line to the output file.
	fprintf(fp, "input,era_sinh,c_sinh\n");
	while (from <= to) {
		sinhera = era_sinh(from);
		sinhc = sinh(from);
		//Write the values to the output file.
		fprintf(fp, "%.17g,%.17g,%.17g\n", from, sinhera, sinhc);
		//If sinhc would be 0 then we would divide by 0 so ignore that case. 
		if (sinhc != 0 && fabs(sinhera-sinhc)/sinhc > worstDeviation) {
			worstDeviation = fabs(sinhera-sinhc)/sinhc;
			worstera = sinhera;
			worstc = sinhc;
			worstInput = from;
		}
		from = from + step;
	}
	printf("The worst relative error was found to be %.17g%% for input %.17g. Our function returned %.17g, the C function returned %.17g.\n", worstDeviation*100, worstInput, worstera, worstc);
}

/*This times our function and the C function in the interval from from to to with a stepsize of step.
 *
 */
void testSpeedInRange(double from, double to, double step) {
	double oldFrom = from;
	long long counter = 0;
	while (from <= to) {
		from = from + step;
		counter = counter + 1;
	}
	from = oldFrom;
	//Time our function
	clock_t start_era = clock();
	while (from <= to) {
		era_sinh(from);
		from = from + step;
	}
	clock_t stop_era = clock();
	
	from = oldFrom;
	//Time the c function
	clock_t start_c = clock();
	while (from <= to) {
		sinh(from);
		from = from + step;
	}
	clock_t stop_c = clock();
	double ourTotalTime = (double)(stop_era - start_era) / CLOCKS_PER_SEC * 1000;
	double cTotalTime = (double)(stop_c - start_c) / CLOCKS_PER_SEC * 1000;
	printf("Our function took %f ms, the C function took %f ms\n", ourTotalTime, cTotalTime);
	printf("That is about %f ms per call for our function.\n", ourTotalTime/(double) counter);
	printf("And about %f ms per call for the C function.\n", cTotalTime/(double) counter);
}

/*This function just asks the user for a double value and calculates the sinh value using
 *our function and the C sinh function and prints both to STDOUT.
 */
void testUserInputValue() {
	double read = readDoubleFromSTDIN("Pleas input a double to test: ");
	printf("era_sinh=%.17g, sinh=%.17g\n", era_sinh(read), sinh(read));
}

/*This function tests all values in the interval from from to to using
 *the nextafter() function. With from = -710 and to = 710 this takes 
 *approximatly 1.5 million years...
 */
void testAllValues(double from, double to) {
	//Used to save the results of our function and the C function.
	double sinhera = era_sinh(from), sinhc = sinh(from);
	//Used to remember the values where the worst deviation orrured.
	double worstera = 0, worstc = 0, worstInput = 0;
	//Used to save the relative error we had there from the C function
	double worstDeviation = 0;
	long long counter = 0;
	while (from != to) {
		sinhera = era_sinh(from);
		sinhc = sinh(from);
		//Just give the user some feedback after a million times through this loop.
		if (counter == 1000000) {
			counter = 0;
			printf("I'm at input value %.17g\n", from);
		}
		//If sinhc would be 0 then we would divide by 0 so ignore that case. 
		if (sinhc != 0 && fabs(sinhera-sinhc)/sinhc > worstDeviation) {
			worstDeviation = fabs(sinhera-sinhc)/sinhc;
			worstera = sinhera;
			worstc = sinhc;
			worstInput = from;
		}
		counter = counter + 1;
		//Get the next value that can be represented by a double in direction of to.
		from = nextafter(from, to);
	}
	printf("The worst relative error was found to be %.17g%% for input %.17g. Our function returned %.17g, the C function returned %.17g.\n", worstDeviation*100, worstInput, worstera, worstc);
}