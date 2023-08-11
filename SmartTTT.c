#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include"tictactoe.h"

int move = O;//initializing move
int board[] = { 1,2,3,4,5,6,7,8,9 };//main board

int variations = 0;//keeps track of variations ai has been thru


    int tictactoe() 
    {
        printf("\n\n\n");
        printBoard();
        int replay = 0;
        //for replaying game
        while (!replay) {


            //for player's move
            if (move == O) {
                printf("\n\n\n                                                     %c's turn\n", 'O');
                int num;
                printf("\n\n\n                                                     Please enter an integer between 1 and 9: ");
                scanf_s("%d", &num);
                while (num <= 0 || num > 9) {
                    printf("\n\n\n                                                     Enter no. from 1 to 9\n");
                    scanf_s("%d", &num);

                }
                if (InsertChar(board, num - 1, move)) {
                    ;
                }
                else {
                    while (!InsertChar(board, num - 1, move)) {
                        printf("\n\n\n                                                     Slot occupied\n\n\n                                                     Please enter a new number: \n");
                        scanf_s("%d", &num);

                    }

                }
            }
            //for ai's move
            else {

                printf("\n\n\n                                                     X's turn\n");
                InsertChar(board, SmartMove(board, 8), x);
                //smartMove function called for first move of computer only
                //smartMove calls minimax for optimal decision
                //depth 8 because 1 move played by human
            }
            system("cls");
            printBoard();
            changemove();

            //to check winner after two moves in a permanently modified board
            int check = CheckWin(board);
            if (check == x) {
                printf("X won!");
                break;
            }
            else if (check == O) {
                printf("O won!");
                break;
            }
            else if (check == 0) {
                printf("Draw!");
                break;


            }

        }
        getchar();
        getchar();
        exit(0);
    }

    int InsertChar(int board_2[], int slot, int replace) {
        if (board_2[slot] == slot + 1) {
            board_2[slot] = replace;
            return 1;
        }
        else {
            return 0;
        }
    }

    //print board function
    //board is a 1D array
    void printBoard() {

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 114);
        printf("                                                    WELCOME TO TIC TAC TOE\n\n");
        printf("                                                     =============\n                                                     | %c | %c | %c |\n                                                     -------------\n                                                     | %c | %c | %c |\n                                                     -------------\n                                                     | %c | %c | %c |\n                                                     =============\n", value(0), value(1), value(2), value(3), value(4), value(5), value(6), value(7), value(8));
        //value function places X,O or position in the printed board array
    }

    char value(int position) {
        // char X and 0 were defined in the beginning as -1 and -2 so they can be stored in int datatype
        int a = board[position];
        if (a == x)
            return 'x';
        else if (a == O)
            return 'O';
        else
            return a + '0';

    }

    void changemove(void) {
        //function has no parameters as move is a global variable
        if (move == x)
        {
            move = O;
        }
        else if (move == O)
        {
            move = x;
        }

    }

    int CheckWin(int board_2[]) {
        int winner = CheckWinner(board_2);
        if (winner == x) {
            return x;
        }
        else if (winner == O) {
            return O;
        }
        else if (winner != x && winner != O) {
            if (drawCheck(board_2)) {
                return 0;
            }
        }
        return 1;
    }

    //CheckWinner returns either X or O
    int CheckWinner(int board_2[]) {
        //look in columns
        for (int i = 0; i < 3; i++) {
            if (board_2[i] == board_2[i + 3] && board_2[i + 3] == board_2[i + 6])
                return board_2[i];
        }

        //look in rows
        for (int i = 0; i < 3; i++) {
            if (board_2[(3 * i)] == board_2[(i * 3) + 1] && board_2[(i * 3) + 1] == board_2[(3 * i) + 2])
                return board_2[(3 * i)];
        }

        //look in diagonals
        //1
        if (board_2[0] == board_2[4] && board_2[4] == board_2[8])
            return board_2[0];
        //2
        if (board_2[2] == board_2[4] && board_2[4] == board_2[6])
            return board_2[2];

        return 0;
    }

    //check for draw
    //looks to see if spaces are occupied
    //1 if draw ; 0 if not draw
    int drawCheck(int board_2[]) {
        for (int i = 0; i < 9; i++) {
            if (board_2[i] == i + 1)
                return 0;
        }
        return 1;
    }


    //function copies board so computer can test moves for max utility without printing on displayed board
    //duplicate board never displayed
    void Duplicate(int original[], int copy[]) {
        for (int i = 0; i < 9; i++) {
            copy[i] = original[i];
        }
    }


    int maxm(int a, int b) {
        return a > b ? a : b;
    }

    int minm(int a, int b) {
        return a < b ? a : b;
    }

    int SmartMove(int board_2[], int depth) {
        system("cls");
        int lArr[9];
        legalMoves(board, lArr);
        int score = -100000;
        int best_score = 0;
        for (int i = 0; i < 9; i++) {
            if (lArr[i]) {
                int DupBoard[9];
                Duplicate(board_2, DupBoard);
                InsertChar(DupBoard, i, x);
                int temp = minimax(DupBoard, depth - 1, 0);
                if (score <= temp) {
                    score = temp;
                    best_score = i;
                }
            }
        }
        return best_score;
    }

    int minimax(int board_2[], int depth, int maximising) {
        int winner = CheckWin(board_2);
        if (winner == x)
        {
            return 10;
        }
        else if (winner == O)
        {
            return -10;
        }
        else if (winner == 0)
        {
            return 0;
        }
        if (depth == 0)
        {
            return 0;
        }

        //SmartMove is maximising
        if (maximising) {
            int score = -100000;
            int lArr[9];
            legalMoves(board_2, lArr);
            for (int i = 0; i < 9; i++) {
                if (lArr[i]) {
                    int DupBoard[9];
                    Duplicate(board_2, DupBoard);
                    InsertChar(DupBoard, i, x);
                    //next move will be human's so minimising utility move
                    score = maxm(minimax(DupBoard, depth - 1, 0), score);
                }
            }
            return score;
        }
        else {
            int score = 1000000;
            int lArr[9];
            legalMoves(board_2, lArr);
            for (int i = 0; i < 9; i++) {
                if (lArr[i]) {
                    int DupBoard[9];
                    Duplicate(board_2, DupBoard);
                    InsertChar(DupBoard, i, O);
                    //next move computer's so maximising=1
                    score = minm(minimax(DupBoard, depth - 1, 1), score);

                }
            }
            return score;

        }

    }
    void legalMoves(int board_2[], int output[]) {
        //checks for freespaces
        for (int i = 0; i < 9; i++) {
            if (board_2[i] == i + 1) {
                output[i] = 1;
            }
            else {
                output[i] = 0;
            }
        }
    }