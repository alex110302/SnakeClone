#include <stdio.h>
#include <stdlib.h>
//* Important you can not have the same include that is already included in a file..
#include "entitylogic.c"

#include "raymath.h"
#include "rcamera.h"


int main()
{
    //* Befor the game loop we will initialize game objects and things of that nature
    //*AKA Game Init Logic n stuff
    InitWindow(1800, 900, "Snake Game");
    SetTargetFPS(60);

    /*
        This code will allocate memory for 10 snake segments while also initializing the first snake segment(the head)
    */
    int snakeInitCap = 10;
    int* pSNakeInitCap = &snakeInitCap;

    SnakeSeg* snakeSeg = (SnakeSeg*)malloc(snakeInitCap * sizeof(SnakeSeg));
    if (snakeSeg == NULL) 
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    snakeSeg[0] = (SnakeSeg){
        true,
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
    
    Food food = {{0,0,0,0},RED,//*dont care about the stuff getting set here besides the bool on the line bellow (thats why they are all 0 and the color does not matter either)
        true
    };
    Food* pFood = &food;

    unsigned int numAliveSnakes = NumOfAliveSnakeSegs(snakeSeg);
    unsigned int* pNumAliveSnakes = &numAliveSnakes;
    unsigned int currentLevel = 0;
    Level startLevel = levels[currentLevel]; 

    InitSnake(snakeSeg, pNumAliveSnakes);



    //* Should Get around to implementing this color for my first level color
    //Color myColor = { 100, 200, 10, 255 };
   
    SnakeStartPos(snakeSeg, startLevel);
   //* main game loop
    while (!WindowShouldClose())
    {
        // for (int i = 0; i <= 9; i++)
        // {
        //     if (snakeSeg[i].isLife == true) printf("%dnd Snake X:%f Y:%f\n", i, snakeSeg[1].Body.x, snakeSeg[1].Body.y);
        // }

        BeginDrawing();
            //*Info Logic
            ClearBackground(DARKGRAY);

            //*level Logic
            DrawLevel(startLevel);

            //*Food Logic
            DrawFood(pFood, startLevel, RED);

            //*Snake Logic
            if (CheckSnakeGrabbedFood(snakeSeg, pFood)) AddNewSnakeSeg(snakeSeg, pFood, pNumAliveSnakes, pSNakeInitCap);

            if (snakeSeg[0].isLife == true) 
            {
                SnakeOutOfBoundsKill(snakeSeg, startLevel);
                DrawAllSnakes(snakeSeg, pNumAliveSnakes);
            }
            else if (snakeSeg[0].isLife == false)
            {
                DrawText("Game Over!\nPress Space To Continue!", 850, 550, 24, WHITE);
                if (IsKeyPressed(KEY_SPACE))
                {
                    snakeSeg[0].isLife = true;
                    SnakeStartPos(snakeSeg, levels[currentLevel]);
                    snakeSeg[0].SnakeDirection = RIGHT;
                } 
            }
            //printf("%d\n", *pNumAliveSnakes);

        EndDrawing();

        //*Non Visual Logic
        if (IsKeyPressed(KEY_ESCAPE)) CloseWindow();
    }

    return 0;
}