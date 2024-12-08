#include "levels.c"

enum EntityDirection 
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct SnakeSeg
{
    int Width;
    int Height;
    int Xpos;
    int Ypos;
    Color SnakeColor;
    enum EntityDirection SnakeDirection;
} SnakeSeg;
//? may want to move this to another file if entity file becomes to crowded (If we need to be divers in entitys)
void MoveSnake(SnakeSeg* snakeSeg,unsigned int snakeIndex)
{
    if (IsKeyPressed(KEY_W)) snakeSeg[snakeIndex].SnakeDirection = UP;
    else if (IsKeyPressed(KEY_D)) snakeSeg[snakeIndex].SnakeDirection = RIGHT;
    else if (IsKeyPressed(KEY_S)) snakeSeg[snakeIndex].SnakeDirection = DOWN;
    else if (IsKeyPressed(KEY_A)) snakeSeg[snakeIndex].SnakeDirection = LEFT;

    if (SecondCountDown(1) > .99)
    {   

        if (snakeSeg[snakeIndex].SnakeDirection == UP) 
        {
            snakeSeg[snakeIndex].Xpos += 0;
            snakeSeg[snakeIndex].Ypos -= 23; 
            snakeSeg[snakeIndex].SnakeDirection = UP;

        }
        else if (snakeSeg[snakeIndex].SnakeDirection == RIGHT)
        {
            snakeSeg[snakeIndex].Xpos += 23;
            snakeSeg[snakeIndex].Ypos += 0;
            snakeSeg[snakeIndex].SnakeDirection = RIGHT;

        } 
        else if (snakeSeg[snakeIndex].SnakeDirection == LEFT) 
        {
            snakeSeg[snakeIndex].Xpos -= 23; 
            snakeSeg[snakeIndex].Ypos += 0;
            snakeSeg[snakeIndex].SnakeDirection = LEFT;
                
        }
        else if (snakeSeg[snakeIndex].SnakeDirection == DOWN) 
        {
            snakeSeg[snakeIndex].Xpos += 0;
            snakeSeg[snakeIndex].Ypos += 23; 
            snakeSeg[snakeIndex].SnakeDirection = DOWN;
        }
    }

    DrawRectangle(
        snakeSeg[snakeIndex].Xpos, 
        snakeSeg[snakeIndex].Ypos, 
        snakeSeg[snakeIndex].Width, 
        snakeSeg[snakeIndex].Height, 
        snakeSeg[snakeIndex].SnakeColor
    );
}