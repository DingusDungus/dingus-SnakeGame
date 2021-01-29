#include "gameTimer.hpp"

namespace clock1 = std::chrono;

void GameTimer::gameTimerStart()
{
    //Starts the timer
    gameTimer = clock1::steady_clock::now();
}

bool GameTimer::foodUpdateReady()
{
    //Checks if food is ready to be updated
    bool foodIsReady = false;
    int secondsPassed = 0;
    clock1::steady_clock::time_point end = clock1::steady_clock::now();
    gameDuration = end - gameTimer;

    secondsPassed = clock1::duration_cast<clock1::seconds>(gameDuration).count();

    if (secondsPassed >= 10)
    {
        foodIsReady = true;
    }

    return foodIsReady;
}

bool GameTimer::modifierFinished()
{
    //Checks if modifier is finished
    bool modifierFinished = false;
    int secondsPassed = 0;
    clock1::steady_clock::time_point end = clock1::steady_clock::now();
    gameDuration = end - gameTimer;

    secondsPassed = clock1::duration_cast<clock1::seconds>(gameDuration).count();

    if (secondsPassed >= 5)
    {
        modifierFinished = true;
    }

    return modifierFinished;
}

bool GameTimer::modifierUpdateReady()
{
    //Checks if modifier is ready to be updated
    bool modifierReady = false;
    int secondsPassed = 0;
    clock1::steady_clock::time_point end = clock1::steady_clock::now();
    gameDuration = end - gameTimer;

    secondsPassed = clock1::duration_cast<clock1::seconds>(gameDuration).count();

    if (secondsPassed >= 15)
    {
        modifierReady = true;
    }

    return modifierReady;
}

void GameTimer::gameTimerReset()
{
    //Resets the timer
    gameTimer = clock1::steady_clock::now();
}
