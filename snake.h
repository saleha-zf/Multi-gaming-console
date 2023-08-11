

#define  UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

 int length;
 int bend_no;
 int len;
 char key;

void load();
int life;
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x, int y);
void Bend();
void Border();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();
int SnakeGame();

struct coordinate
{
    int x;
    int y;
    int direction;
};

typedef  struct coordinate coordinate;

coordinate head, bend[500], food, body[30];


