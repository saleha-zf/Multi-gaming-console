#define x -1
#define O -2


int maxm(int a, int b);
int minm(int a, int b);
void printBoard();
void changemove();
int InsertChar(int board_2[], int slot, int replace);
char value(int position);
int CheckWinner(int baord_2[]);
int CheckWin(int board_2[]);
int drawCheck(int board_2[]);
void Duplicate(int original[], int copy[]);
int minimax(int board_2[], int depth, int maximising);
int SmartMove(int board_2[], int depth);
void legalMoves(int board_2[], int output[]);
int tictactoe(); 