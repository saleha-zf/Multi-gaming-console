// Main menu program that allows user to select a game of their choice.

#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include "snake.h"
#include "tictactoe.h"

int n = 0;
char Pointer[3] = { '>', ' ', ' ' };

void MenuPrint() {

    for (int i = 10; i < 38; i++)
    {

        GotoXY(i, 10);
        printf("%c", 219);
    }
       
       for (int i = 10; i < 25; i++)
       {
           GotoXY(10, i);
           printf("%c", 219);
           GotoXY(38, i);
           printf("%c", 219);
       }
    gotoxy(40, 13); //Centers the text.

    printf("\n\n  ");
    printf("\t\t   MAIN MENU\t\t\n  \n ");
    printf("\t\t%c Snake Game \n", Pointer[0]);
    printf("\t\t%c Tic Tac Toe \n", Pointer[1]);
    printf("\t\t%c Wordle \n", Pointer[2]);
    
    for (int i = 10; i < 39; i++)
    {
        GotoXY(i, 25);
        printf("%c", 219);
    }

}

void GameSelect() {
    if (n % 3 == 0) {
        SnakeGame(); //Starts the snake game.
    }
    else if (n % 3 == 1) {
        tictactoe(); //Starts the Tic Tac Toe game.
    }
    else if (n % 3 == 2) {
        Wordle(); //Starts the Wordle Game.
    }
}

int main() {

    while (1) {
        //This is the code for the arrow key navigation.
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        MenuPrint(); 
        int InputKey = _getch();

        //If enter is pressed, you go into the respective game.
        if (InputKey == 13) {
            system("cls");
            GameSelect();
        }

        //Case for arrow down and up respectively.
        else if (InputKey == 80) {
            n++;
        }
        else if (InputKey == 72) {
            n--;
        }

        //Makes the array blank spaces and then adds a > to whichever place in the array corresponds with n%3.
        for (int i = 0; i < 3; i++) {
            Pointer[i] = ' ';
        }

        Pointer[n % 3] = '>';
        
        system("cls");

    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //To reset the console to default colours.

    return 0;
}