#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>

char InputWord[5];
//The following initializer adds all the words in the .txt file into the array from which a random word is selected.
//It's efficient because it does not clutter the code with hundreds of words and is faster than secondary storage reading.
char Words[][6] = {
#include "Words.txt"
};

char OutputWord[5];
char ExistingWord[5];
char Attempts[6][5] = {0};
char ColorCodeAttempts[6][5];


//This function checks whether or not the letter in question is in the word that has been chosen by the randomizer.
int IsLetterInWord(int i) {
	for (int j = 0; j < 5; j++) {
		if (InputWord[i] == ExistingWord[j]) return 1;
	}
	return 0;
}

//This function checks whether or not the letter is in the correct place in the input compared to the word chosen.
int IsLetterInPlace(int i) {
	if (InputWord[i] == ExistingWord[i]) {
		return 1;
	}
	else {
		return 0;
	}
}

//This function checks whether or not the win condition has been reached.
int WinCondition() {
	int flag = 0;
	for (int w = 0; w < 5; w++) {
		if (OutputWord[w] != 'R') flag = 1;
	}
	if (flag == 0) return 1;
	else return 0;
}

//This function prints the color code key for the game.
void KeyPrint() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
	printf("  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf(" = Letter is in correct place.\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 111);
	printf("  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf(" = Letter exists in the word.\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 143);
	printf("  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf(" = Letter does not exist in the word.\n");
}

//This function prints out all the attempts/board that have been made so far with an appropriate number of rows and appropriate colors.
void PrintAttempts(int Row) {
	for (int a = 0; a <= Row; a++) {
		for (int b = 0; b < 5; b++) {
			if (Attempts[Row][b] != 0) {
				if (ColorCodeAttempts[a][b] == 'R') {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
					printf(" %c ", Attempts[a][b]);
				}
				if (ColorCodeAttempts[a][b] == 'E') {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 111);
					printf(" %c ", Attempts[a][b]);
				}
				if (ColorCodeAttempts[a][b] == 'W') {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 143);
					printf(" %c ", Attempts[a][b]);
				}
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("\n---------------\n");
	}
}

//This function contains most of the calls to other functions, takes inputs and gives outputs.
void Attempt() {
	int NumTries = 1;
	int Row = 0;
	while (1) {
		//The following code prints basic information.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("WELCOME TO WORDLE!\nGuess the five letter word.\nYou have six attempts.\n\n");
		printf("Key:\n");
		KeyPrint();

		printf("\nTHIS IS ATTEMPT #%d\n", NumTries);

		printf("\nInput word: ");
		gets(InputWord);

		//Error checking for anything other than a 5 character string.
		if (strlen(InputWord) > 5 || strlen(InputWord) < 5) {
			printf("\nBad input. Please input a five letter word.\nPress enter to try again.");
			getchar();
			system("cls");
			continue;
		}

		//Taking uppercase/lowercase into account.
		for (int j = 0; j < 5; j++) {
			if ((InputWord[j] > 96) && (InputWord[j] < 123)) {
				InputWord[j] = toupper(InputWord[j]);
			}
		}

		//Copies the input into the result board.
		for (int k = 0; k < 5; k++) {
			Attempts[Row][k] = InputWord[k];
		}
		printf("\n");

		//Checks the correctness of the input compared to the word that is being played for.
		for (int i = 0; i < 5; i++) {

			if (IsLetterInWord(i)) {
				if (IsLetterInPlace(i)) {
					OutputWord[i] = 'R';
				}
				else OutputWord[i] = 'E';
			}
			else OutputWord[i] = 'W';
		}

		//Takes the E/R/W letter key to code the color of the places in the output board.
		for (int b = 0; b < 5; b++) {
			ColorCodeAttempts[Row][b] = OutputWord[b];
		}

		printf("Results so far:\n---------------\n");
		PrintAttempts(Row);

		//Checking if player has won.
		if (WinCondition()) {
			printf("\nYOU WIN!\n");
			getchar();
			exit(0);
		}
		else {
			NumTries++;
			Row++;
		}

		//Gives continue prompt.
		if (NumTries <= 6) {
			printf("\nPress enter to do next attempt.");
			getchar();
			system("cls");
		}
		//Checking if player has lost.
		if (NumTries == 7) {
			printf("\nThe correct word was ");
			puts(ExistingWord);
			printf("YOU LOSE!\n");
			getchar();
			exit(0);
		}
	}
}

int Wordle() {
	srand(time(0));
	int x = rand() % 580;

	for (int a = 0; a < 5; a++) {
		ExistingWord[a] = Words[x][a]; //Selects a random word from the Words.txt file.
	}

	Attempt();

	return 0;
}