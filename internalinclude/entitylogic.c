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
    bool isHead;
    bool isLife;
    Rectangle Body;
    //?Might wanna use these last vars to ditermin where the next snakeseg should go
    double LastXpos;
    double LastYpos;
    Color SnakeColor;
    enum EntityDirection SnakeDirection;
} SnakeSeg;
//? may want to move this to another file if entity file becomes to crowded (If we need to create more than one type of entity)

//*prototypes
void MoveSnakeSegs(SnakeSeg* snakeSeg, unsigned int* pNumOfAliveSnakes);
void DrawAllSnakes(SnakeSeg* snakeSeg, unsigned int* pNumOfAliveSnakes);
void DrawSnake(SnakeSeg* snakeSeg, unsigned int snakeIndex);
unsigned int NumOfAliveSnakeSegs(SnakeSeg* SnakeSeg);
void AddNewSnakeSeg(SnakeSeg* snakeSeg, Food* pFood, unsigned int* numOfAliveSnakes, int* initNumSnakeSegs);
bool CheckSnakeGrabbedFood(SnakeSeg* snakeHead, Food* pFood);
void MoveSnake(SnakeSeg* snakeSeg,unsigned int snakeIndex, unsigned int* pNumOfAliveSnakes);
void SnakeStartPos(SnakeSeg* snakeHead, Level level);
void SnakeOutOfBoundsKill(SnakeSeg* snakeSeg, Level level);

void MoveSnake(SnakeSeg* snakeSeg, unsigned int snakeIndex, unsigned int* pNumOfAliveSnakes)
{
    if (IsKeyPressed(KEY_W)) snakeSeg[0].SnakeDirection = UP;
    else if (IsKeyPressed(KEY_D)) snakeSeg[0].SnakeDirection = RIGHT;
    else if (IsKeyPressed(KEY_S)) snakeSeg[0].SnakeDirection = DOWN;
    else if (IsKeyPressed(KEY_A)) snakeSeg[0].SnakeDirection = LEFT;

    if (SecondCountDown(1) > .99)
    {   
        if (snakeSeg[0].SnakeDirection == UP) 
        {
            snakeSeg[0].LastXpos = snakeSeg[0].Body.x;
            snakeSeg[0].LastYpos = snakeSeg[0].Body.y;
            snakeSeg[0].Body.x += 0;
            snakeSeg[0].Body.y -= 20; 
            snakeSeg[0].SnakeDirection = UP;

        }
        else if (snakeSeg[0].SnakeDirection == RIGHT)
        {
            snakeSeg[0].LastXpos = snakeSeg[0].Body.x;
            snakeSeg[0].LastYpos = snakeSeg[0].Body.y;
            snakeSeg[0].Body.x += 20;
            snakeSeg[0].Body.y += 0;
            snakeSeg[0].SnakeDirection = RIGHT;

        } 
        else if (snakeSeg[0].SnakeDirection == LEFT) 
        {
            snakeSeg[0].LastXpos = snakeSeg[0].Body.x;
            snakeSeg[0].LastYpos = snakeSeg[0].Body.y;
            snakeSeg[0].Body.x -= 20; 
            snakeSeg[0].Body.y += 0;
            snakeSeg[snakeIndex].SnakeDirection = LEFT;
                
        }
        else if (snakeSeg[0].SnakeDirection == DOWN) 
        {
            snakeSeg[0].LastXpos = snakeSeg[0].Body.x;
            snakeSeg[0].LastYpos = snakeSeg[snakeIndex].Body.y;
            snakeSeg[0].Body.x += 0;
            snakeSeg[0].Body.y += 20; 
            snakeSeg[0].SnakeDirection = DOWN;
        }

        MoveSnakeSegs(snakeSeg, pNumOfAliveSnakes);
        //printf("Body.x:%d Body.y:%d\n", snakeSeg[snakeIndex].Body.x, snakeSeg[snakeIndex].Body.y);
        //printf("Snake IndexNum:%d Body.x:%f Body.y:%f LastXPos:%d LastYPos:%d\n", snakeIndex, snakeSeg[snakeIndex].Body.x, snakeSeg[snakeIndex].Body.y, snakeSeg[snakeIndex].LastXpos, snakeSeg[snakeIndex].LastYpos);
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

        snakeSeg[*pNumOfAliveSnakes] = (SnakeSeg){
            false,
            true,
            {
                snakeSeg[*pNumOfAliveSnakes - 1].LastXpos,
                snakeSeg[*pNumOfAliveSnakes - 1].LastYpos,
                20,
                20
            },
            0,
            0,
            SNAKE_COLOR,
            snakeSeg[*pNumOfAliveSnakes - 1].SnakeDirection
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
    for (int i = 0; i < *pNumOfAliveSnakes; i++) 
    {
        MoveSnake(snakeSeg, i, pNumOfAliveSnakes);
    }
}

void MoveSnakeSegs(SnakeSeg* snakeSeg, unsigned int* pNumOfAliveSnakes)
{
    printf("snake head-> SHX:%f SHLX:%f SHY:%f SHLY:%f\n", snakeSeg[0].Body.x, snakeSeg[0].LastXpos, snakeSeg[0].Body.y, snakeSeg[0].LastYpos); 
    for (int i = 0; i < *pNumOfAliveSnakes; i++)
    {
        if (snakeSeg[i].isHead == false)
        {
            //printf("snakesegindex:%d\n", i);
            snakeSeg[i].Body.x = snakeSeg[i - 1].LastXpos;
            snakeSeg[i].Body.y = snakeSeg[i - 1].LastYpos;
            snakeSeg[i].LastXpos = snakeSeg[i].Body.x;
            snakeSeg[i].LastYpos = snakeSeg[i].Body.y;
        }

        printf("snake index:%d X:%f LX:%f Y:%f LY:%f\n", i, snakeSeg[i].Body.x, snakeSeg[i].LastXpos, snakeSeg[i].Body.y, snakeSeg[i].LastYpos);
    }
}