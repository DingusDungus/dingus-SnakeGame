#ifndef GAME_TIMER_HPP
#define GAME_TIMER_HPP
#include <chrono>

class GameTimer
{
public:
    //handles in-game timed actions, such as food spawning and modifier spawning
    void gameTimerStart();
    void gameTimerReset();
    bool foodUpdateReady();
    bool modifierUpdateReady();
    bool modifierFinished();

private:
    std::chrono::steady_clock::time_point gameTimer;

    std::chrono::steady_clock::duration gameDuration;
};

#endif