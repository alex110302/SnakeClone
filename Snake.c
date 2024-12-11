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
        true,
        {
            0,
            0,
            20,
            20
        },
        0,
        0,
        SNAKE_COLOR,
        RIGHT
    };

    unsigned int currnetLevel = 0;
    Level startLevel = levels[currnetLevel]; 

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
            DrawLevel(startLevel);

            //*Snake Logic
            if (snakeSeg[0].isLife == true) 
            {
                SnakeOutOfBoundsKill(snakeSeg, startLevel);
                MoveSnake(snakeSeg, 0);
            }
            else if (snakeSeg[0].isLife == false)
            {
                DrawText("Game Over!", 850, 550, 24, WHITE);
                if (IsKeyPressed(KEY_SPACE))
                {
                    snakeSeg[0].isLife = true;
                    SnakeStartPos(snakeSeg, levels[currnetLevel]);
                    snakeSeg[0].SnakeDirection = RIGHT;
                } 
            }

        EndDrawing();

        //*Non Visual Logic
        if (IsKeyPressed(KEY_ESCAPE)) CloseWindow();
    }

    return 0;
}