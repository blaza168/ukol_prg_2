#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MODE_EASY 0
#define MODE_NORMAL 1
#define MODE_HARD 2

#define NUMBER_OF_ROUNDS 3


/*
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	CODE FORMAT: Function with less format number can call only function with hier layer (except utils)
	layer number can be calculated as number of '_' before function
	every value MUST have assigned value -1 in initialization
	
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

// utils
void uCenterCursor(int lineDown);
void uClearConsole();

// first layer of functions
// first screen
void _renderWelcomeScreen(); // render welcome screen

int _getDifficulty();	// returns difficulty game difficulty or -1 if input was invalid

void _pause(); // wait for user

// game
bool _play(int round, int number, int input, int difficulty);
int _generateNumber(int difficulty);

void _renderWinScreen();
void _renderLoseScreen();


// second layer of functions
// welcome screen
int __integerToMode(int input); // returns MODE_* or -1 for invalid input

// game
int __getMaximumNumber(int difficulty);
int __getUserInput(int max); // returns user input | -1 if failed

void __renderGameScreen(int round, int secret, int input);

// third layer
// game
char* __getHint(int secret, int input);








int main() {
	
	int difficulty = -1;
	int secretNumber = -1;
	
	do {
		_renderWelcomeScreen();
		difficulty = _getDifficulty();
		uClearConsole();
	} while (difficulty == -1);
	
	uClearConsole();
	
	secretNumber = _generateNumber(difficulty);
	
	if (_play(1, secretNumber, -1, difficulty)) {
		uClearConsole();
		_renderWinScreen();
	} else {
		uClearConsole();
		_renderLoseScreen();
	}
	
	_pause();
}
















// utils

void uCenterCursor(int lineDown) {
	for (int i = 0; i < lineDown; i++) {
		printf("\n");
	}
	
	for (int i = 0; i < 54; i++) {
		printf(" ");
	}
}

void uClearConsole() {
	system("cls");
}

// first layer

void _renderWelcomeScreen() {
	uCenterCursor(10);
	
	printf("CHOOSE DIFFICULTY");
	uCenterCursor(1);
	printf("=================");
	
	uCenterCursor(1);
	
	printf(">>>  EASY (1)  <<<");
	
	uCenterCursor(1);
	
	printf(">>> MEDIUM (2) <<<");
	
	uCenterCursor(1);
	
	printf(">>>  HARD (3)  <<<");
	
	uCenterCursor(2);
	
	printf("Your choose: ");
}

int _getDifficulty() {
	int choose;
	
	scanf("%d", &choose);
	
	return __integerToMode(choose);
}

void _pause() {
	system("PAUSE > NULL");
}

bool _play(int round, int number, int input, int difficulty) {
	if (round == NUMBER_OF_ROUNDS + 1) {
		return false;
	}
	
	uClearConsole();
	
	int maxNumber = __getMaximumNumber(difficulty);
	
	do {
		__renderGameScreen(round, number, input);
	
		input = __getUserInput(maxNumber);
	} while(input == -1);
	
	if (input == number) {
		return true;
	}
	
	return _play(round + 1, number, input, difficulty);
}

int _generateNumber(int difficulty) {
	srand(time(NULL));
	
	int devideBy = __getMaximumNumber(difficulty) + 1;
	
	
	return rand() % devideBy;
}

void _renderLoseScreen() {
	printf("You lose :-(");
}

void _renderWinScreen() {
	printf("You won !!!");
}

// second layer
// welcome screen
int __integerToMode(int input) {
	switch(input) {
		case 1:
			return MODE_EASY;
		case 2:
			return MODE_NORMAL;
		case 3:
			return MODE_HARD;
		
		default:
			return -1;
	}
}

// game
int __getMaximumNumber(int difficulty) {
	if (difficulty == MODE_EASY) {
		return 20;
	}
	
	if (difficulty == MODE_NORMAL) {
		return 50;
	}
	
	if (difficulty == MODE_HARD) {
		return 100;
	}
	
	printf("EXCEPTION!!!! in __getMaximumNumber(int difficulty) uknkown difficulty mode '%d'", difficulty);
	return -1; // throw devided by zero exception
}


int __getUserInput(int max) {
	int input = -1;
	
	scanf("%d", &input);
	
	if (input > max || input < 0) {
		return -1;
	}
	
	return input;
}

void __renderGameScreen(int round, int secret, int input) {
	uCenterCursor(10);
	
	printf("Round: %d", round);
	uCenterCursor(1);
	
	if (input != -1) {
		printf("%s", __getHint(secret, input));	
	}
	
	uCenterCursor(2);
	printf("Enter your next tip: ");
}

// third layer
// game

char* __getHint(int secret, int input) {
	if (secret > input) {
		return "Secret is bigger";
	} else {
		return "Secret number is lower";
	}
}



