#include <stdio.h>
#include <stdlib.h>
//* IMPORTATNT you can not have the smae include that is alrady inclooded in a file..
#include "entitylogic.c"

#include "raymath.h"
#include "rcamera.h"


int main()
{
    //* Befor the game loop we will initalize game objects and things of that nautre

    InitWindow(1800, 900, "Snake Game");
    SetTargetFPS(60);

    /*
        This code will allocate memeory for 10 snake segments while also initlaizing the first snake segmanet(the head)
    */
    int snakeInitCap = 10;
    int currentSnakeSize = 1;

    SnakeSeg* snakeSeg = (SnakeSeg*)malloc(snakeInitCap * sizeof(SnakeSeg));
    if (snakeSeg == NULL) 
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    snakeSeg[0] = (SnakeSeg){
        20,
        20,
        0,
        0,
        0,
        0,
        SNAKE_COLOR,
        RIGHT
    };

    Level startLevel = levels[0]; 
    unsigned int currentlyLoadedLevel = 0; //TODO: get ride of this var and change the code the depend on it to fit the line above this one

    //* Should Get arround to impliemnting this color for my first level color
    Color myColor = { 100, 200, 10, 255 };
   
    SnakeStartPos(snakeSeg, startLevel);
   //* main game loop
    while (!WindowShouldClose())
    {

        BeginDrawing();

            //*Info Logic
            ClearBackground(DARKGRAY);

            //*level Logic
            DrawLevel(currentlyLoadedLevel);

            //*Snake Logic
            MoveSnake(snakeSeg, 0);


            if (SnakeOutOfBoundsKill(snakeSeg, startLevel)) 
            {
                if (SecondCountDown(5) > 4.5) printf("SNAKE IS OUT OF BOUNDS!!!!\n");
                // free(snakeSeg);
                // snakeSeg = NULL;
            }
            else 
            {
                //MoveSnake(snakeSeg, 0);
            }

        EndDrawing();

        //*Non Visual Logic
        if (IsKeyPressed(KEY_SPACE)) CloseWindow();
    }

    return 0;
}