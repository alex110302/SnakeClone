#include <math.h>
#include <time.h>
#include "customcolors.c"

//not fully acerate because it will only update when the next frame is drawn
double SecondCountDown(double startSeconds)
{
    double elapsedTime = fmod(startSeconds - GetTime(), startSeconds);
    if (elapsedTime < 0) elapsedTime += startSeconds;
    return elapsedTime;
}

/*
    Does what it says duhhhhhhh dot dot dot 

    which means returning a random number 
    between the given min and max... 
*/
int RandMinMax(int min, int max)
{  
    srand(GetTime() * 100000 * time(0));
    return (rand() % (max - min + 1)) + min;
}

//returns a random number
int RandNumber()
{
    srand(GetTime() * 100000 * time(0));
    return rand();
}

//?should come back and make it so you can get any random number that is devisable by a given number ex for func signature could be      int RandNum(int min, int max, int modNum, int divisibleBy)
/*
    This function works like RandMinMax
    But it takes into account the game gird 
    Which every square is 20 by 20 in the level 
    so it makes sure that the random number
    given back is a number that is evenly 
    devisable by 20
*/
int GridRandMinMax(int min, int max)
{  
    int randNum = RandMinMax(min, max);

    if (randNum % 20 != 0)
    {
        int tempRandNum = randNum;

        int firstDigit = tempRandNum % 10;
        if (firstDigit != 0) firstDigit = 0;
        tempRandNum = tempRandNum / 10;

        int secondDigit = tempRandNum % 10;
        if (secondDigit % 2 != 0) 
        {
            if (secondDigit >= 5) secondDigit += 1;
            else secondDigit -= 1;
        }
        tempRandNum = tempRandNum / 10;
        
        randNum = tempRandNum * 100 + secondDigit * 10 + firstDigit; 
    }

    return randNum;
}

//?should look into making a foreach function in the future to help make things easier