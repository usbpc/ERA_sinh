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
	double sinhera = era_sinh(from), sinhc = sinh(from);
	double worstera = 0, worstc = 0, worstInput = 0;
	double worstDeviation = 0;
	fprintf(fp, "input,era_sinh,c_sinh\n");
	while (from <= to) {
		sinhera = era_sinh(from);
		sinhc = sinh(from);
		fprintf(fp, "%.17g,%.17g,%.17g\n", from, sinhera, sinhc);
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
	printf("And about %f ms per call for the C function.", cTotalTime/(double) counter);
}

void testUserInputValue() {
	double read = readDoubleFromSTDIN("Pleas input a double to test: ");
	printf("era_sinh=%.17g, sinh=%.17g\n", era_sinh(read), sinh(read));
}

void testAllValues(double from, double to) {
	double sinhera = era_sinh(from), sinhc = sinh(from);
	double worstera = 0, worstc = 0, worstInput = 0;
	double worstDeviation = 0;
	long long counter = 0;
	while (from != to) {
		sinhera = era_sinh(from);
		sinhc = sinh(from);
		if (counter == 1000000) {
			counter = 0;
			printf("I'm at input value %.17g\n", from);
		}
		if (sinhc != 0 && fabs(sinhera-sinhc)/sinhc > worstDeviation) {
			worstDeviation = fabs(sinhera-sinhc)/sinhc;
			worstera = sinhera;
			worstc = sinhc;
			worstInput = from;
		}
		counter = counter + 1;
		from = nextafter(from, to);
	}
	printf("The worst relative error was found to be %.17g%% for input %.17g. Our function returned %.17g, the C function returned %.17g.\n", worstDeviation*100, worstInput, worstera, worstc);
}