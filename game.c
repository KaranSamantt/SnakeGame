#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define W 40
#define H 20    //we defined the game boundaries using macros
#define T 100   // so we can easily resize the game without changing the logic here


int x,y;    //head position of snake
int score , gameOver;   // variables for player score and game over
int fx , fy;   // POSItion of FOOD
int len = 0;    // snake length
int tx[T],ty[T];    //x and Y position of tail
char dir;    // it will be used for storing direction
HANDLE h;    //refrence to console
COORD c;     //it is used for cursor position (x,y)

char playerName[20];   // <-- PLAYER NAME

// this is cursor movement function
void go(int x,int y)
{
    c.X=x;    //this will prevent screen flickering
    c.Y=y;
    SetConsoleCursorPosition(h,c); //makes game smooth,and give poition to circle
}


// this is the first challenge we encountered and we used this fuction to resolve it
void hide()
{
    CONSOLE_CURSOR_INFO ci = {1,0};
    SetConsoleCursorInfo(h,&ci);
}


// colours function
void color(int c)
{
    SetConsoleTextAttribute(h,c);
}


//START SCREEN
void startScreen()
{
    system("cls");
    color(10);  // green
    printf("\n\n\t\tSNAKE GAME\n"); //we added a start screen so the user understands
                                   // controls before gameplay begins.
    color(14); // yellow
    printf("\t====================\n");
    color(7);

    printf("\tControls:\n");
    printf("\t\tW - Up\n");
    printf("\t\tA - Left\n");
    printf("\t\tS - Down\n");
    printf("\t\tD - Right\n");
    printf("\t\tX - Exit\n");

    printf("\n\tPress any key to start...");
    _getch(); // wait for key
}


// GAME SETUP
void setup()
{
    srand(time(0));

    x = W/2; //the snake will start from center
    y = H/2;

    dir = 'r';  //snake start moving right
    score = 0; //thjs is used to reset game values
    gameOver = 0;
    len = 0;

    fx = rand()%(W-2)+1; //this is so that the position of food doest not appear
    fy = rand()%(H-2)+1;    //on and outside the border
}


// DRAW GAME
void draw()
{
    go(0,0); //here this will move cursor to top left to redraw

    color(14); // yellow
    for(int i=0;i<W+2;i++) printf("#"); //this will draw top and bottom walls
    puts("");

    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
            if(j==0) printf("#"); // left border

            if(i==y && j==x)
            {
                color(10); // gives green colour of snake head
                printf("O");//snake head shape
            }
            else if(i==fy && j==fx)
            {
                color(12); // gives red colour food
                printf("*");
            }
            else
            {
                int body=0;
                for(int k=0;k<len;k++) //tail poition
                {
                    if(tx[k]==j && ty[k]==i)
                    {
                        color(10); //  gived green colour body of snake
                        printf("o"); // shape of body
                        body=1;
                        break;
                    }  //The snake body is stored using arrays
                }  //where each index represents one segment.

                if(body==0)
                {
                    color(7);
                    printf(" ");
                }
            }

            if(j==W-1)
            {
                color(14); // yellow
                printf("#"); // right border
            }
        }
        puts("");
    }

    color(14);
    for(int i=0;i<W+2;i++) printf("#");

    color(11); // cyan
    printf("\nScore: %d",score);
}


// INPUT HANDLING
void input()
{
    if(_kbhit()) //this is use to press key and tkae input without stopping the game
    {
        char ch;
        ch = _getch();

        if(ch=='w') dir='u'; //this will update direction
        else if(ch=='s') dir='d';
        else if(ch=='a') dir='l';
        else if(ch=='d') dir='r';

        if(ch=='x')
            gameOver=1;//helps exit game
    }
}


// GAME LOGIC
void logic()
{
    int px = tx[0], py = ty[0];
    int px2 , py2;

    tx[0]=x; //this is used so that tail stays with head
    ty[0]=y;

    for(int i=1;i<len;i++)
    {
        px2 = tx[i];
        py2 = ty[i];

        tx[i]=px;
        ty[i]=py;

        px=px2;
        py=py2;
    }

    if(dir=='u') y--; //move snake based on dircetion
    if(dir=='d') y++;
    if(dir=='l') x--;
    if(dir=='r') x++;

    if(x<0 || x>=W) gameOver=1; //this will end game if snake hits the wall
    if(y<0 || y>=H) gameOver=1;

    for(int i=0;i<len;i++)
    {
        if(tx[i]==x && ty[i]==y)
        {
            gameOver=1;  //this helps overing the game is snake hit itself
        }
    }

    if(x==fx && y==fy)
    {
        score+=10;  //increases score after eating the food
        len++; //increases snake length after eating the food

        fx = rand()%(W-2)+1;
        fy = rand()%(H-2)+1; //generates new food position
    }
}

// SAVE NAME + SCORE (APPEND MODE)
void saveScore(char name[], int score)
{
    FILE *fp = fopen("scores.txt", "a");

    if(fp != NULL)
    {
        fprintf(fp, "%s --> %d\n", name, score);
        fclose(fp);
    }
}

int main()
{
    h = GetStdHandle(STD_OUTPUT_HANDLE); //gets console handle
    hide();

     // GET PLAYER NAME
    system("cls");
    color(11);       //COLOR GIVEN
    printf("Enter your name: ");
    scanf("%19s", playerName);     // READ NAME


    startScreen(); // welcome screen
    setup();//intialise everything

    while(!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(120); //game loop
    }

    go(0,H+4);
    color(12);
    printf("GAME OVER | FINAL SCORE: %d",score); //game over screen
    color(7);

    saveScore(playerName, score);

    return 0;
}
