#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

class GameState
{
public:
    static int const IN_GAME = 1;
    static int const PLAYER_LOST = 3;
    static int const PLAYER_QUIT = 4;

    GameState() { state = IN_GAME; }
    void setInGame() { state = IN_GAME; }
    void setPlayerLost() { state = PLAYER_LOST; }
    void setPlayerQuit() { state = PLAYER_QUIT; }

    bool isInGame() const { return state == IN_GAME; }
    bool playerLost() const { return state == PLAYER_LOST; }
    bool playerQuit() const { return state == PLAYER_QUIT; }

    int getState() const { return state; }

private:
    int state;
};

#endif