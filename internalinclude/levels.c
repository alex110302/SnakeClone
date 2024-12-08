#include "gamelogic.c"

typedef struct Level
{
    int Height;
    int Width;
    Color BackgroundColor;
    //? might want to add some additinal level inforamting at some point
} Level;

//* I am going to manually put new levels in here
Level levels[] = {
    {
        400,
        400,
        {
            0,
            252,
            18,
            255
        }   
    },
    {
        600,
        600,
        {
            0,
            172,
            13,
            255
        }   
    }
};

void DrawLevel(unsigned int levelIndex)
{
    DrawRectangle(
        700,
        250,
        levels[levelIndex].Width, 
        levels[levelIndex].Height,
        levels[levelIndex].BackgroundColor 
    );
}

