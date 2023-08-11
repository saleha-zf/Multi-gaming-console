#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include "snake.h"

void Move() //basic function to display food coordinates and change the x y moving coordinates.
{ //Regenerates the snake characters at new coordinates continuously.
	
	//this function calls Left() Right() Up() Down() functions to check which key user pressed.
    int a, i;

    do
    {

        Food();
        fflush(stdin); //removes previous alocation of memory

        len = 0;

        for (i = 0; i < 30; i++)

        {

            body[i].x = 0;

            body[i].y = 0;

            if (i == length)

                break;

        }

        Delay(length); // the speed of the characters is propotional to it's length

        Border();

        if (head.direction == RIGHT)

            Right();

        else if (head.direction == LEFT)

            Left();

        else if (head.direction == DOWN)

            Down();

        else if (head.direction == UP)

            Up();

        ExitGame();

    } while (!_kbhit());

    a = _getch();

    if (a == 27)

    {
        system("cls");
        exit(0);

    }
    key = _getch();

    if ((key == RIGHT && head.direction != LEFT && head.direction != RIGHT) || (key == LEFT && head.direction != RIGHT && head.direction != LEFT) || (key == UP && head.direction != DOWN && head.direction != UP) || (key == DOWN && head.direction != UP && head.direction != DOWN))

    {

        bend_no++;

        bend[bend_no] = head;

        head.direction = key;

        if (key == UP)

            head.y--;

        if (key == DOWN)

            head.y++;

        if (key == RIGHT)

            head.x++;

        if (key == LEFT)

            head.x--;

        Move();

    }

    else if (key == 27)

    {

        system("cls");

        exit(0);

    }

    else

    {

        printf("\a");

        Move();

    }
}

void gotoxy(int x, int y) //fetches and sets new (x,y) coordinates using COORD structure. 
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout); //using fflush to remove previous memory allocation so that only new characters are displayed
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, b);
}
void load() //Shows a loading screen by displaying ASCII characters using a large valued loop.
{

    int row, col, r, c, q;
    gotoxy(36, 14);
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    printf("loading...");
    gotoxy(30, 15);
    for (r = 1; r <= 20; r++)
    {
        for (q = 0; q <= 10000000; q++); //to display the character slowly
        printf("%c", 177);
    }

    _getch();
}
void Down()
{
    int i;
    for (i = 0; i <= (head.y - bend[bend_no].y) && len < length; i++)
    {
        GotoXY(head.x, head.y - i);
        {
            if (len == 0)
                printf("v");
            else
                printf("%c", 186);
        }
        body[len].x = head.x;
        body[len].y = head.y - i;
        len++;
    }
    Bend();
    if (!_kbhit())
        head.y++;
}
void Delay(long double k) //Slows down the speed by using a large-valued loop.
{
    Score();
    long double i;
    for (i = 0; i <= (50000000); i++);
}
void ExitGame()
{
    int i, check = 0;
    for (i = 4; i < length; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if (body[0].x == body[i].x && body[0].y == body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if (i == length || check != 0)
            break;
    }
    if (head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30 || check != 0)
    {
        life--;
        if (life >= 0)
        {
            head.x = 25;
            head.y = 20;
            bend_no = 0;
            head.direction = RIGHT;
            Move();
        }
        else
        {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            printf("\n\tAll lives completed\n\tYour score is %d\n\tPress any key to quit the game\n",Scoreonly());

            getchar();
            exit(0);
        }
    }
}
void Food()//Generates food characters randomly.
//The length of snake increases when head of snake aligns with food coordinates.
{

    if (head.x == food.x && head.y == food.y)
    {
        length++;
        time_t a;
        a = time(0);
        srand(a);
        food.x = rand() % 70;
        if (food.x <= 10)
            food.x += 11;
        food.y = rand() % 30;
        if (food.y <= 10)

            food.y += 11;
    }
    else if (food.x == 0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        food.x = rand() % 70;
        if (food.x <= 10)
            food.x += 11;
        food.y = rand() % 30;
        if (food.y <= 10)
            food.y += 11;
    }
}
void Left()
{
    int i;
    for (i = 0; i <= (bend[bend_no].x - head.x) && len < length; i++)
    {
        GotoXY((head.x + i), head.y);
        {
            if (len == 0)
                printf("<");
            else
                printf("%c", 205);
        }
        body[len].x = head.x + i;
        body[len].y = head.y;
        len++;
    }
    Bend();
    if (!_kbhit())
        head.x--;

}
void Right()
{
    int i;
    for (i = 0; i <= (head.x - bend[bend_no].x) && len < length; i++)
    {
        //GotoXY((head.x-i),head.y);
        body[len].x = head.x - i;
        body[len].y = head.y;
        GotoXY(body[len].x, body[len].y);
        {
            if (len == 0)
                printf(">");
            else
                printf("%c", 205);
        }
        /*body[len].x=head.x-i;
        body[len].y=head.y;*/
        len++;
    }
    Bend();
    if (!_kbhit())
        head.x++;
}
void Bend() //Relocates the snake characters after a bend and exchanges the snake coordinates.
{
    int i, j, diff;
    for (i = bend_no; i >= 0 && len < length; i--)
    {
        if (bend[i].x == bend[i - 1].x)
        {
            diff = bend[i].y - bend[i - 1].y;
            if (diff < 0)
                for (j = 1; j <= (-diff); j++)
                {
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y + j;
                    GotoXY(body[len].x, body[len].y);
                    printf("%c", 186);
                    len++;
                    if (len == length)
                        break;
                }
            else if (diff > 0)
                for (j = 1; j <= diff; j++)
                {

                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y - j;
                    GotoXY(body[len].x, body[len].y);
                    printf("%c", 186);
                    len++;
                    if (len == length)
                        break;
                }
        }
        else if (bend[i].y == bend[i - 1].y)
        {
            diff = bend[i].x - bend[i - 1].x;
            if (diff < 0)
                for (j = 1; j <= (-diff) && len < length; j++)
                {
                   
                    body[len].x = bend[i].x + j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    printf("%c", 205);
                    len++;
                    if (len == length)
                        break;
                }
            else if (diff > 0) //bending downwards
                for (j = 1; j <= diff && len < length; j++)
                {
                   
                    body[len].x = bend[i].x - j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    printf("%c", 205);
                    len++;
                    if (len == length)
                        break;
                }
        }
    }
}
void Border() //Displays gameboard using ASCII; Life decrements when snake and border align
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);

    int i;
    GotoXY(food.x, food.y);   //displays food
    printf("%c", 233);
    for (i = 10; i < 71; i++)
    {
        GotoXY(i, 10);
        printf("%c", 254);
        GotoXY(i, 30);
        printf("%c", 254);
    }
    for (i = 10; i < 31; i++)
    {
        GotoXY(10, i);
        printf("%c", 254);
        GotoXY(70, i);
        printf("%c", 254);
    }
}
void Print() //Displays game instructions in the beginning.
{

    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 142);

    //GotoXY(10,12);
    printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
    _getch();
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n> Use arrow keys to move the snake.\n\n > You will be provided food at the several coordinates of the screen.\n\n > Eating a food increases the length and score by 1.\n\n > You have three lives. Life decreases as you hit the wall or snake's body.\n\n > Pause the game by pressing any key. Press any key again to resume the game.\n\n > Press ESC to exit. \n");
    printf("\n\nPress any key to play the game...");
    if (_getch() == 27)
        exit(0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
}

int Score() //Shows score and life count depending on length of the snake.
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    int score;
    GotoXY(20, 8);
    score = length - 5;
    printf("SCORE : %d", (length - 5));
    score = length - 5;
    GotoXY(50, 8);
    printf("Life : %d", life);
    return score;
}
int Scoreonly() //only returns the score value
{
    int score = Score();
    system("cls");
    return score;
}
void Up()
{
    int i;
    for (i = 0; i <= (bend[bend_no].y - head.y) && len < length; i++)
    {
        GotoXY(head.x, head.y + i);
        {
            if (len == 0)
                printf("^");
            else
                printf("%c", 186);
        }
        body[len].x = head.x;
        body[len].y = head.y + i;
        len++;
    }
    Bend();
    if (!_kbhit())
        head.y--;
}

int SnakeGame() //main function to be called in the menu
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 63);

    Print();

    system("cls");
  
    load();

    length = 5;

    head.x = 25;

    head.y = 20;

    head.direction = RIGHT;

    Border();

    Food(); //to generate food coordinates initially

    life = 3; //number of extra lives

    bend[0] = head;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);
    Move();   //initialing initial bend coordinate

    return 0;
}