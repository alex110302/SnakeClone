#include <math.h>
#include "customcolors.c"

//not fully acurate because it will only update when the next frame is drawn
double SecondCountDown(double startSeconds)
{
    double elaspedTime = fmod(startSeconds - GetTime(), startSeconds);
    if (elaspedTime < 0) elaspedTime += startSeconds;
    return elaspedTime;
}

