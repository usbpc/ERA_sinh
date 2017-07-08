#include <stdio.h>
#include "selecttest.h"

enum States {
	ENTRY,
	SELECTTEST,
	END
};

void changeState(int input, enum States *state) {
	printf("\x1b[2J\x1b[1;1H");
	switch(input) {
		case -1:
			*state = ENTRY;
		case 0:
			*state = END;
			break;
		case 1:
			*state = SELECTTEST;
			break;
		default:
			printf("I didn't recognize that option, so lets go to the beginning...\n");
			*state = ENTRY;


	}
}

int main() {
	enum States state = ENTRY;
	printf("Welcome to the test programm for our sinh() function. Please select what you want to do.\n");
	for (;;) {
		int input;
		switch(state) {
		case ENTRY:
			printf("0) End this programm\n");
			printf("1) Read numbers to test from lines in SelectionInput.txt in the current directory.\n");
			printf("2) errortest\n");
			printf("3) quicktesterror\n");
			printf("4) quicktestspeed\n");
			printf("5) quicktestboth\n");
			printf("6) longtestboth\n");
			printf("Please select what you want to do: ");
			scanf("%d", &input);
			changeState(input, &state);
			break;
		case SELECTTEST:
			selecttest();
			changeState(-1, &state);
		case END:  
			goto main_end;
		default:
			state = ENTRY;
		}
	}
	main_end: printf("%s\n", "Exit State, bye <3");
}