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

double SecondCountDown(double startSeconds);

void MoveSnake(SnakeSeg* snakeSeg, int snakeIndex);

int main()
{
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
    int horizontalMove;
    int verticalMove;

    if (SecondCountDown(1) > .97)
    {   
        
        // if (IsKeyReleased(KEY_A)) 
        // {
        //     // horizontalMove -= 23;
        //     // verticalMove += 0;
        //     snakeSeg[snakeIndex].Xpos -= 23; 
        //     snakeSeg[snakeIndex].Ypos += 0;
                
        // }
        // else if (IsKeyReleased(KEY_W)) 
        // {
        //     // verticalMove -= 23;
        //     // horizontalMove += 0;
        //     snakeSeg[snakeIndex].Ypos -= 23; 
        //     snakeSeg[snakeIndex].Xpos += 0;
        // }
        // else if (IsKeyReleased(KEY_S)) 
        // {
        //     // verticalMove += 23;
        //     // horizontalMove += 0;
        //     snakeSeg[snakeIndex].Ypos += 23; 
        //     snakeSeg[snakeIndex].Xpos += 0;
        // }
        // else if (IsKeyReleased(KEY_D))
        // {
        //     // horizontalMove += 23;
        //     // verticalMove += 0;
        //     snakeSeg[snakeIndex].Xpos += 23;
        //     snakeSeg[snakeIndex].Ypos += 0;
        // }


        if (IsKeyDown(KEY_A)) 
        {
            horizontalMove = 23;
            verticalMove = 0;
            // snakeSeg[snakeIndex].Xpos -= 23; 
            // snakeSeg[snakeIndex].Ypos += 0;
                
        }
        else if (IsKeyDown(KEY_W)) 
        {
            verticalMove = 23;
            horizontalMove = 0;
            // snakeSeg[snakeIndex].Ypos -= 23; 
            // snakeSeg[snakeIndex].Xpos += 0;
        }
        else if (IsKeyDown(KEY_S)) 
        {
            verticalMove = 23;
            horizontalMove = 0;
            // snakeSeg[snakeIndex].Ypos += 23; 
            // snakeSeg[snakeIndex].Xpos += 0;
        }
        else if (IsKeyDown(KEY_D))
        {
            horizontalMove = 23;
            verticalMove = 0;
            // snakeSeg[snakeIndex].Xpos += 23;
            // snakeSeg[snakeIndex].Ypos += 0;
        } 

        

        // snakeSeg[snakeIndex].Xpos -= horizontalMove; 
        // snakeSeg[snakeIndex].Ypos -= verticalMove; 

        // if (IsKeyReleased(KEY_A) || IsKeyReleased(KEY_W))
        // {
        //     snakeSeg[snakeIndex].Xpos = horizontalMove; 
        //     snakeSeg[snakeIndex].Ypos = verticalMove; 
        // }
        // if (IsKeyReleased(KEY_D) || IsKeyReleased(KEY_S))
        // {
        //     snakeSeg[snakeIndex].Ypos = verticalMove; 
        //     snakeSeg[snakeIndex].Xpos = horizontalMove;
        // }
    }


    DrawRectangle(
        snakeSeg[snakeIndex].Xpos, 
        snakeSeg[snakeIndex].Ypos, 
        snakeSeg[snakeIndex].Width, 
        snakeSeg[snakeIndex].Height, 
        snakeSeg[snakeIndex].SnakeColor
    );
}

//not fully acurate because it will only update when the next frame is drawn
double SecondCountDown(double startSeconds)
{
    double elaspedTime = fmod(startSeconds - GetTime(), startSeconds);
    if (elaspedTime < 0) elaspedTime += startSeconds;
    return elaspedTime;
}