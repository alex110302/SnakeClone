#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"


/*
    We could do something with the position the the SnakeSeg to determin weather or not its the head or something
*/
typedef struct SnakeSeg
{
    int Width;
    int Height;
    int Xpos;
    int Ypos;
    Color SnakeColor;
} SnakeSeg;

int main()
{
    InitWindow(1800, 900, "Hello, World!");
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
        }
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();

        Color myColor = { 100, 200, 10, 255 };

        ClearBackground(myColor);

        DrawText("Hello World!, This is my first RayLib Project", 100, 100, 20, RED);

        if (IsKeyDown(KEY_A)) snakeSeg[0].Xpos -= 13; 
        if (IsKeyDown(KEY_W)) snakeSeg[0].Ypos -= 13; 
        if (IsKeyDown(KEY_S)) snakeSeg[0].Ypos += 13; 
        if (IsKeyDown(KEY_D)) snakeSeg[0].Xpos += 13; 


        DrawRectangle(snakeSeg[0].Xpos, snakeSeg[0].Ypos, snakeSeg[0].Width, snakeSeg[0].Height, snakeSeg[0].SnakeColor);

        EndDrawing();

        if (IsKeyDown(KEY_SPACE)) CloseWindow();

    }
    

    return 0;
}



