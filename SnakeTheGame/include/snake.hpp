#ifndef SNAKE_HPP
#define SNAKE_HPP
#include <ncurses.h>
#include <vector>

#include "positionSystem.hpp"
#include "direction.hpp"
#include "gameState.hpp"
#include "gameTimer.hpp"
#include "difficulty.hpp"
#include "gameModifier.hpp"
#include "HighscoreHandler.hpp"
#include "positionHandler.hpp"

class SnakeGame
{
    //Main class of the snake game
public:
    //CONSTRUCTORS/DESTRUCTORS
    SnakeGame();
    ~SnakeGame();

    //SNAKE_FUNCTIONS
    void moveSnake();

    //USER_INPUT_FUNCTIONS
    void userGameInput(const char &key);

    //GET_FUNCTIONS
    int getBoardHeight() const;
    int getBoardWidth() const;
    int getGameState() const;
    int getCurrentScore() const;
    int getGameDifficulty() const;

    //ANIMATION_FUNCTIONS
    void playerLostSeq(WINDOW *window);
    void refreshPositionSystem(WINDOW *window);

private:
    positionHandler posHandler;

    Direction direction;
    GameState gamestate;
    GameTimer foodtimer;
    GameTimer modifierTimer;
    GameTimer modifierInterval;
    HighscoreHandler highscorehandler;

    GameModifier gameModifier;
    Difficulty gameDifficulty;

    int unsigned snake_length;
    int unsigned currentScore;
    int const DEFAULT_SNAKE_LENGTH = 5;

    int const BOARD_HEIGHT = 25;
    int const BOARD_WIDTH = 100;

    struct SnakeNode
    {
        int unsigned yValue;
        int unsigned xValue;
        SnakeNode *Next;
        SnakeNode(const int &yValue, const int &xValue) : yValue(yValue), xValue(xValue), Next(nullptr) {}
    };

    SnakeNode *head;
    SnakeNode *backtail;
    SnakeNode *oldBacktailPos;

    //DELETE_FUNCTIONS
    void deleteSnake();

    //GENERATE_FUNCTIONS
    void generatePositionSystem();
    void generateSnake();

    //SNAKE_FUNCTIONS
    void growSnake();
    void moveHeadPosition();

    //SET_FUNCTIONS
    void setSnake();

    //CHECK_FUNCTIONS
    void wallCheck();
    void snakeBodyCheck();
    void foodCheck();
    void foodUpdate();
    void modifierCheck();

    //MODIFIER_FUNCTIONS
    void modifierUpdate();
    void randomModifier();
    void halfSnake();
};

#endif