#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sinh.h"
#include "functions.h"
#include "tests.h"

enum States {
	ENTRY,
	RANGETEST,
	SPEEDTEST,
	SPEEDTESTPOS,
	SPEEDTESTNEG,
	USERINPUT,
	ALLVALUESMAYBE,
	ALLVALUES,
	END
};

//This function handels the changing of states
void changeState(int input, enum States *state) {
	switch(input) {
		case -1:
			*state = ENTRY;
			break;
		case 0:
			if (*state == ALLVALUESMAYBE) {
				*state = ENTRY;
			} else {
				*state = END;
			}
			break;
		case 1:
			if (*state == ALLVALUESMAYBE) {
				*state = ALLVALUES;
			} else {
				*state = RANGETEST;
			}
			break;
		case 2:
			*state = SPEEDTEST;
			break;
		case 3:
			*state = SPEEDTESTPOS;
			break;
		case 4:
			*state = SPEEDTESTNEG;
			break;
		case 5:
			*state = USERINPUT;
			break;
		case 6:
			*state = ALLVALUESMAYBE;
			break;
		default:
			*state = ENTRY;


	}
}

int main() {
	enum States state = ENTRY;
	clearScreen();
	printf("Welcome to the test programm for our sinh() function. Please select what you want to do.\n");
	for (;;) {
		int input;
		//This switch statement deals with calling the right functions and outputting the menu
		switch(state) {
		case ENTRY:
			printf("0) End this programm\n");
			printf("1) Test numbers from -710 to 710 in steps of 0.01 write all outputs into a .csv file.\n");
			printf("2) Compare the speed of our programm to the C function with testing numbers from -710 to 710 in steps of 0.001.\n");
			printf("3) Compare the speed of our programm to the C function with testing numbers from 0 to 710 in steps of 0.001.\n");
			printf("4) Compare the speed of our programm to the C function with testing numbers from -710 to 0 in steps of 0.001.\n");
			printf("5) Input a double and see the value our function and the C function returns.\n");
			printf("6) Test all possible values from -710 to 710 and output the value where our function has the most relative error to the C function.\n");
			printf("Please select what you want to do: ");
			scanf("%d", &input);
			clearScreen();
			changeState(input, &state);
			break;
		case RANGETEST:
			clearScreen();
			FILE *fp = createFile("rangetest");
			testValuesInRange(-710, 710, 0.01, fp);
			fclose(fp);
			changeState(-1, &state);
			break;
		case SPEEDTEST:
			clearScreen();
			testSpeedInRange(-710, 710, 0.001);
			changeState(-1, &state);
			break;
		case SPEEDTESTPOS:
			clearScreen();
			testSpeedInRange(0, 710, 0.001);
			changeState(-1, &state);
			break;
		case SPEEDTESTNEG:
			clearScreen();
			testSpeedInRange(-710, 0, 0.001);
			changeState(-1, &state);
			break;
		case USERINPUT:
			clearScreen();
			testUserInputValue();
			changeState(-1, &state);
			break;
		case ALLVALUESMAYBE:
			clearScreen();
			printf("Are you sure? This takes a really really really long time!\n");
			printf("0) No please take me back to the main menu.\n");
			printf("1) Yes, I know what I am doing.\n");
			printf("Please select what you want to do: ");
			scanf("%d", &input);
			changeState(input, &state);
			clearScreen();
			break;
		case ALLVALUES:
			printf("Well you wanted it, here we go...\n");
			testAllValues(-710, 710);
			changeState(-1, &state);
			break;
		case END:  
			goto main_end;
		default:
			state = ENTRY;
		}
	}
	main_end: printf("%s\n", "Bye <3");
}