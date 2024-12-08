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
        500,
        500,
        {
            255,
            255,
            255,
            255
        },
        RIGHT
    };

    //* not using this right now but want to for main level background color
    Color myColor = { 100, 200, 10, 255 };
   
   //* main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        DrawLevel(0);

        MoveSnake(snakeSeg, 0);

        EndDrawing();

        if (IsKeyDown(KEY_SPACE)) CloseWindow();
    }

    return 0;
}