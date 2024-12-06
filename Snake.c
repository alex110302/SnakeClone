#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"


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

void MoveSnake(SnakeSeg* snakeSeg, int snakeIndex);

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

    Color myColor = { 100, 200, 10, 255 };
   
    while (!WindowShouldClose())
    {
        BeginDrawing();


        ClearBackground(myColor);

        DrawText("Hello World!, This is my first RayLib Project", 100, 100, 20, RED);

        MoveSnake(snakeSeg, 0);

        EndDrawing();

        if (IsKeyDown(KEY_SPACE)) CloseWindow();

    }
    

    return 0;
}

void MoveSnake(SnakeSeg* snakeSeg, int snakeIndex)
{
    double gameTime = GetTime();
    double moveTime;
    if (true)
    //need to find a way to get only half a second or so to determin when to move
    if (true)
    
        if (IsKeyDown(KEY_A)) snakeSeg[snakeIndex].Xpos -= 13; 
        if (IsKeyDown(KEY_W)) snakeSeg[snakeIndex].Ypos -= 13; 
        if (IsKeyDown(KEY_S)) snakeSeg[snakeIndex].Ypos += 13; 
        if (IsKeyDown(KEY_D)) snakeSeg[snakeIndex].Xpos += 13; 


    DrawRectangle(
        snakeSeg[snakeIndex].Xpos, 
        snakeSeg[snakeIndex].Ypos, 
        snakeSeg[snakeIndex].Width, 
        snakeSeg[snakeIndex].Height, 
        snakeSeg[snakeIndex].SnakeColor
    );
}


