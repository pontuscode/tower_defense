#include "Timer.h"

Timer::Timer()
{
    clock.restart();
    isPaused = false;
    runTime = 0.0f;
}

void Timer::pauseTimer()
{
    if(!isPaused)
    {
        runTime += clock.getElapsedTime().asSeconds();
    }
    isPaused = true;
}

void Timer::resumeTimer()
{
    if(isPaused)
    {
        clock.restart();
    }
    isPaused = false;
}
    
float Timer::getTimer()
{
    if(!isPaused)
    {
        return runTime + clock.getElapsedTime().asSeconds();
    }
    else if(isPaused)
    {
        clock.restart();
    }
    return runTime;
}

void Timer::resetTimer()
{
    runTime = 0.0f;
    clock.restart();
}
