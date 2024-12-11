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
    //? might want to add some additinal level inforamting at some point
} Level;

typedef struct Food
{
    Rectangle Area;
    Color FoodColor;
    //? May add some special properties at some point
} Food;

//* I am going to manually put new levels in here
Level levels[] = {
    {
        {
            700, //TODO: wnat to make this automatic
            250, //TODO: want to make this automatic
            400,
            400,
        },
        750, //TODO: want to make this automatic
        300, //TODO: wnat to make this automatic
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

//!this no work so itll break when we try to call the function above
//!But I need ti impliment something like this        int random_number = (rand() % (max - min + 1)) + min;
//this draws food at random position with the level
/*
void DrawFood(Level level, Color foodColor)
{
    Food food;
    food.Area.x = RandPosInLevel(RAND_X_POS);
    food.Area.y = RandPosInLevel(RAND_Y_POS);
    food.Area.height = 20;
    food.Area.width = 20;
    food.FoodColor = foodColor;

    DrawRectangle(
        food.Area.x,
        food.Area.y,
        food.Area.width,
        food.Area.height,
        food.FoodColor
    );
}

int RnadPosInLevel(enum RandPosXY randPosXY)
{   
    
    switch (randPosXY)
    {
        case RAND_X_POS:
           
        return ;
        case RAND_Y_POS:
        
        return ;
    }
    
}
*/
void InitSnakeStartPosForLevl(Level level)
{
    //level.DrawXpos = some math thing
   //level.DrawYpos = some math thing
    //level.StartXpos = some math thing
    //level.StartYpos = some math thing
}
