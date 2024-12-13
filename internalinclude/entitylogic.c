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
    bool isLife;
    Rectangle Body;
    //?Might wanna use these last vars to determin where the next snakeseg should go
    int LastXpos;
    int LastYpos;
    Color SnakeColor;
    enum EntityDirection SnakeDirection;
} SnakeSeg;
//? may want to move this to another file if entity file becomes to crowded (If we need to create more than one tpye of entity)

//*Prototyps
unsigned int NumOfAliveSnakeSegs(SnakeSeg* SnakeSeg);
void AddNewSnakeSeg(SnakeSeg* snakeSeg, Food* pFood, unsigned int* numOfAliveSnakes, int* initNumSnakeSegs);
bool CheckSnakeGrabedFood(SnakeSeg* snakeHead, Food* pFood);
void MoveSnake(SnakeSeg* snakeSeg,unsigned int snakeIndex);
void SnakeStartPos(SnakeSeg* snakeHead, Level level);
bool SnakeOutOfBoundsKill(SnakeSeg* snakeHead,Level level);

void MoveSnake(SnakeSeg* snakeSeg, unsigned int snakeIndex)
{
    if (IsKeyPressed(KEY_W)) snakeSeg[snakeIndex].SnakeDirection = UP;
    else if (IsKeyPressed(KEY_D)) snakeSeg[snakeIndex].SnakeDirection = RIGHT;
    else if (IsKeyPressed(KEY_S)) snakeSeg[snakeIndex].SnakeDirection = DOWN;
    else if (IsKeyPressed(KEY_A)) snakeSeg[snakeIndex].SnakeDirection = LEFT;

    if (SecondCountDown(1) > .99)
    {   

        if (snakeSeg[snakeIndex].SnakeDirection == UP) 
        {
            snakeSeg[snakeIndex].LastXpos = snakeSeg[snakeIndex].Body.x;
            snakeSeg[snakeIndex].LastYpos = snakeSeg[snakeIndex].Body.y;
            snakeSeg[snakeIndex].Body.x += 0;
            snakeSeg[snakeIndex].Body.y -= 20; 
            snakeSeg[snakeIndex].SnakeDirection = UP;

        }
        else if (snakeSeg[snakeIndex].SnakeDirection == RIGHT)
        {
            snakeSeg[snakeIndex].LastXpos = snakeSeg[snakeIndex].Body.x;
            snakeSeg[snakeIndex].LastYpos = snakeSeg[snakeIndex].Body.y;
            snakeSeg[snakeIndex].Body.x += 20;
            snakeSeg[snakeIndex].Body.y += 0;
            snakeSeg[snakeIndex].SnakeDirection = RIGHT;

        } 
        else if (snakeSeg[snakeIndex].SnakeDirection == LEFT) 
        {
            snakeSeg[snakeIndex].LastXpos = snakeSeg[snakeIndex].Body.x;
            snakeSeg[snakeIndex].LastYpos = snakeSeg[snakeIndex].Body.y;
            snakeSeg[snakeIndex].Body.x -= 20; 
            snakeSeg[snakeIndex].Body.y += 0;
            snakeSeg[snakeIndex].SnakeDirection = LEFT;
                
        }
        else if (snakeSeg[snakeIndex].SnakeDirection == DOWN) 
        {
            snakeSeg[snakeIndex].LastXpos = snakeSeg[snakeIndex].Body.x;
            snakeSeg[snakeIndex].LastYpos = snakeSeg[snakeIndex].Body.y;
            snakeSeg[snakeIndex].Body.x += 0;
            snakeSeg[snakeIndex].Body.y += 20; 
            snakeSeg[snakeIndex].SnakeDirection = DOWN;
        }

        //printf("Body.x:%f Body.y:%f\n", snakeSeg[snakeIndex].Body.x, snakeSeg[snakeIndex].Body.y);
    }

    //!NEED TO IMPLIMENT ADDING NEW SNAKE SEG TO SCREEN
    DrawRectangle(
        snakeSeg[snakeIndex].Body.x, 
        snakeSeg[snakeIndex].Body.y, 
        snakeSeg[snakeIndex].Body.width, 
        snakeSeg[snakeIndex].Body.height, 
        snakeSeg[snakeIndex].SnakeColor
    );
}

void SnakeStartPos(SnakeSeg* snakeHead, Level level)
{
    snakeHead[0].Body.x = level.StartXpos;
    snakeHead[0].Body.y = level.StartYpos;
}

bool SnakeOutOfBoundsKill(SnakeSeg* snakeHead,Level level)
{  
    if (CheckCollisionRecs(snakeHead[0].Body, level.Area)) return false;
    snakeHead[0].isLife = false;
    return true;
}

bool CheckSnakeGrabedFood(SnakeSeg* snakeHead, Food* pFood)
{
    if (CheckCollisionRecs(snakeHead[0].Body, pFood->Area))
    {
        pFood->Gotten = true;
        return true;
    }

    return false;
}

void AddNewSnakeSeg(SnakeSeg* snakeSeg, Food* pFood, unsigned int* pNumOfAliveSnakes, int* pSNakeInitCap)
{
    if (CheckCollisionRecs(snakeSeg[0].Body, pFood->Area))
    {
        if (*pNumOfAliveSnakes + 1 > *pSNakeInitCap) return; //!we need to allocate more memory for more snkae segs

        snakeSeg[*pNumOfAliveSnakes + 1] = (SnakeSeg){
            true,
            {
                snakeSeg[*pNumOfAliveSnakes].LastXpos,
                snakeSeg[*pNumOfAliveSnakes].LastYpos,
                20,
                20
            },
            0,
            0,
            SNAKE_COLOR,
            snakeSeg[*pNumOfAliveSnakes].SnakeDirection
        };

        *pNumOfAliveSnakes = NumOfAliveSnakeSegs(snakeSeg);
    }
}

unsigned int NumOfAliveSnakeSegs(SnakeSeg* snakeSeg)
{
    unsigned int numInitSnakeSegs = 0;
    for(int i = 0; i <= 9; i++) if (snakeSeg[i].isLife == true) numInitSnakeSegs++;
    return numInitSnakeSegs;
}