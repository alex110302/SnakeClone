#include "levellogic.c"

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
    //?Might wanna use these last vars to determin where the next snakeseg should go
    int LastXpos;
    int LastYpos;
    Color SnakeColor;
    enum EntityDirection SnakeDirection;
} SnakeSeg;
//? may want to move this to another file if entity file becomes to crowded (If we need to create more than one tpye of entity)
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
            snakeSeg[snakeIndex].LastXpos = snakeSeg[snakeIndex].Xpos;
            snakeSeg[snakeIndex].LastYpos = snakeSeg[snakeIndex].Ypos;
            snakeSeg[snakeIndex].Xpos += 0;
            snakeSeg[snakeIndex].Ypos -= 23; 
            snakeSeg[snakeIndex].SnakeDirection = UP;

        }
        else if (snakeSeg[snakeIndex].SnakeDirection == RIGHT)
        {
            snakeSeg[snakeIndex].LastXpos = snakeSeg[snakeIndex].Xpos;
            snakeSeg[snakeIndex].LastYpos = snakeSeg[snakeIndex].Ypos;
            snakeSeg[snakeIndex].Xpos += 23;
            snakeSeg[snakeIndex].Ypos += 0;
            snakeSeg[snakeIndex].SnakeDirection = RIGHT;

        } 
        else if (snakeSeg[snakeIndex].SnakeDirection == LEFT) 
        {
            snakeSeg[snakeIndex].LastXpos = snakeSeg[snakeIndex].Xpos;
            snakeSeg[snakeIndex].LastYpos = snakeSeg[snakeIndex].Ypos;
            snakeSeg[snakeIndex].Xpos -= 23; 
            snakeSeg[snakeIndex].Ypos += 0;
            snakeSeg[snakeIndex].SnakeDirection = LEFT;
                
        }
        else if (snakeSeg[snakeIndex].SnakeDirection == DOWN) 
        {
            snakeSeg[snakeIndex].LastXpos = snakeSeg[snakeIndex].Xpos;
            snakeSeg[snakeIndex].LastYpos = snakeSeg[snakeIndex].Ypos;
            snakeSeg[snakeIndex].Xpos += 0;
            snakeSeg[snakeIndex].Ypos += 23; 
            snakeSeg[snakeIndex].SnakeDirection = DOWN;
        }

        printf("Xpos:%d Ypos:%d\n", snakeSeg[snakeIndex].Xpos, snakeSeg[snakeIndex].Ypos);
    }


    DrawRectangle(
        snakeSeg[snakeIndex].Xpos, 
        snakeSeg[snakeIndex].Ypos, 
        snakeSeg[snakeIndex].Width, 
        snakeSeg[snakeIndex].Height, 
        snakeSeg[snakeIndex].SnakeColor
    );
}

void SnakeStartPos(SnakeSeg* snakeHead, Level level)
{
    snakeHead[0].Xpos = level.StartXpos;
    snakeHead[0].Ypos = level.StartYpos;
}

bool SnakeOutOfBoundsKill(SnakeSeg* snakeHead,Level level)
{   
    //! CURRENT TODO
    //TODO: Fix this logic so it can tell what if its in our out of bounds
    if (snakeHead[0].Xpos <= level.Height || snakeHead[0].Ypos <= level.Width ) return true;
    return false;
}