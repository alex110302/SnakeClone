#include "gamelogic.c"

typedef struct Level
{
    Rectangle Area;
    int StartXpos;
    int StartYpos;
    Color BackgroundColor;
    //? might want to add some additinal level inforamting at some point
} Level;

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

void InitSnakeStartPosForLevl(Level level)
{
    //level.DrawXpos = some math thing
   //level.DrawYpos = some math thing
    //level.StartXpos = some math thing
    //level.StartYpos = some math thing
}
