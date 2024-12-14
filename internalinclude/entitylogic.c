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
    //?Might wanna use these last vars to ditermin where the next snakeseg should go
    int LastXpos;
    int LastYpos;
    Color SnakeColor;
    enum EntityDirection SnakeDirection;
} SnakeSeg;
//? may want to move this to another file if entity file becomes to crowded (If we need to create more than one type of entity)

//*prototypes
void DrawAllSnakes(SnakeSeg* snakeSeg, unsigned int* pNumOfAliveSnakes);
void DrawSnake(SnakeSeg* snakeSeg, unsigned int snakeIndex);
unsigned int NumOfAliveSnakeSegs(SnakeSeg* SnakeSeg);
void AddNewSnakeSeg(SnakeSeg* snakeSeg, Food* pFood, unsigned int* numOfAliveSnakes, int* initNumSnakeSegs);
bool CheckSnakeGrabbedFood(SnakeSeg* snakeHead, Food* pFood);
void MoveSnake(SnakeSeg* snakeSeg,unsigned int snakeIndex);
void SnakeStartPos(SnakeSeg* snakeHead, Level level);
void SnakeOutOfBoundsKill(SnakeSeg* snakeSeg, Level level);

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
            printf("LastXpos:%f LastYpos:%f\n", snakeSeg[snakeIndex].LastXpos, snakeSeg[snakeIndex].LastYpos);
            snakeSeg[snakeIndex].Body.x += 0;
            snakeSeg[snakeIndex].Body.y += 20; 
            snakeSeg[snakeIndex].SnakeDirection = DOWN;
        }

        printf("Body.x:%f Body.y:%f\n", snakeSeg[snakeIndex].Body.x, snakeSeg[snakeIndex].Body.y);
        //!The last positions are not getting set...
        //printf("LastXpos:%f LastYpos:%f\n", snakeSeg[snakeIndex].LastXpos, snakeSeg[snakeIndex].LastYpos);

    }

   DrawSnake(snakeSeg, snakeIndex);
}

void SnakeStartPos(SnakeSeg* snakeHead, Level level)
{
    snakeHead[0].Body.x = level.StartXpos;
    snakeHead[0].Body.y = level.StartYpos;
}

void SnakeOutOfBoundsKill(SnakeSeg* snakeSeg, Level level)
{  
    if (CheckCollisionRecs(snakeSeg[0].Body, level.Area)) snakeSeg[0].isLife = true;
    else snakeSeg[0].isLife = false;
}

bool CheckSnakeGrabbedFood(SnakeSeg* snakeHead, Food* pFood)
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
        if (*pNumOfAliveSnakes + 1 > *pSNakeInitCap) return; //!we need to allocate more memory for more snake segs

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

//?I should get around to moving the InitSnakeCap var to here in the entity logic file or something 
//Returns the number of snake segs that exists
unsigned int NumOfAliveSnakeSegs(SnakeSeg* snakeSeg)
{
    unsigned int numInitSnakeSegs = 0;
    for (int i = 0; i <= 9; i++) if (snakeSeg[i].isLife == true) numInitSnakeSegs++;
    return numInitSnakeSegs;
}

//simply Draws A Snake... atm put in 0 to get the snake head
void DrawSnake(SnakeSeg* snakeSeg, unsigned int snakeIndex)
{
     DrawRectangle(
        snakeSeg[snakeIndex].Body.x, 
        snakeSeg[snakeIndex].Body.y, 
        snakeSeg[snakeIndex].Body.width, 
        snakeSeg[snakeIndex].Body.height, 
        snakeSeg[snakeIndex].SnakeColor
    ); 
}

void DrawAllSnakes(SnakeSeg* snakeSeg, unsigned int* pNumOfAliveSnakes)
{
    for (int i = 0; i <= *pNumOfAliveSnakes; i++) MoveSnake(snakeSeg, i);
}