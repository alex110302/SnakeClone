#include "gamelogic.c"

enum RandPosXY
{
    RAND_X_POS,
    RAND_Y_POS
};        

typedef struct Level
{
    Rectangle Area;
    int StartXpos;
    int StartYpos;
    Color BackgroundColor;
    //? might want to add some additional level information at some point
} Level;

typedef struct Food
{
    Rectangle Area;
    Color FoodColor;
    bool Gotten;
    //? May add some special properties at some point
} Food;

//*prototypes
void DrawLevel(Level level);
void DrawFood(Food* pFood, Level level, Color foodColor);
int RandPosInLevel(Level level, enum RandPosXY randPosXY);
void InitSnakeStartPosForLevel(Level level);


//* I am going to manually put new levels in here
Level levels[] = {
    {
        {
            700, //TODO: want to make this automatic
            250, //TODO: want to make this automatic
            400,
            400,
        },
        760, //TODO: want to make this automatic
        300, //TODO: want to make this automatic
        {
            0,
            252,
            18,
            255
        }   
    },
    { //! THIS WILL NOT DRAW RIGHT!!! NEED TO SET THE DRAW X AND Y VARS CORRECTLY
        {
            0,
            0,
            600,
            600,
        },
        0,
        0,
        {
            0,
            172,
            13,
            255
        }   
    }
};

//?level logic... need to specify because I am to lazy to move the food logic into its own thing
//Draws the given level
void DrawLevel(Level level)
{
    DrawRectangle(
        level.Area.x, 
        level.Area.y, 
        level.Area.width, 
        level.Area.height,
        level.BackgroundColor 
    );
}


int RandPosInLevel(Level level, enum RandPosXY randPosXY)
{   
    switch (randPosXY)
    {
        case RAND_X_POS: return GridRandMinMax(level.Area.x, level.Area.width);
        case RAND_Y_POS: return GridRandMinMax(level.Area.y, level.Area.height);
        default: return 0;
    }
}

void InitSnakeStartPosForLevel(Level level)
{
    //level.DrawXpos = some math thing
   //level.DrawYpos = some math thing
    //level.StartXpos = some math thing
    //level.StartYpos = some math thing
}

//?Food Logic ... should move this to another file to lazy rn
//this draws food at random position with the level
void DrawFood(Food *pFood, Level level, Color foodColor)
{

    if (pFood->Gotten)
    {
        pFood->Area.x = RandPosInLevel(level, RAND_X_POS);
        pFood->Area.y = RandPosInLevel(level, RAND_Y_POS);
        pFood->Gotten = false;
    }

    //printf("Food-Xpos:%f Food-Ypos:%f\n",pFood->Area.x ,pFood->Area.y);

    pFood->Area.height = 20;
    pFood->Area.width = 20;
    pFood->FoodColor = foodColor;

    DrawRectangle(
        pFood->Area.x,
        pFood->Area.y,
        pFood->Area.width,
        pFood->Area.height,
        pFood->FoodColor
    );
}
