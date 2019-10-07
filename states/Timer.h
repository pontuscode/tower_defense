#pragma once
#include <SFML/Graphics.hpp>
//Vi ville ha en klocka som vi kunde pausa tiden med. Eftersom det inte går att pausa en sf::Clock så gjorde vi denna klassen, där runTime är det som representerar tiden medan clock tickar på som vanligt. runTime är det som returneras när   vi vill komma åt tiden från andra klasser och funktioner. 
class Timer
{
public:
    Timer();
    ~Timer() = default;
    
    void pauseTimer();
    void resumeTimer();
    float getTimer();
    void resetTimer();

private:   
    sf::Clock clock;   
    bool isPaused;
    float runTime = 0.0f;
};
