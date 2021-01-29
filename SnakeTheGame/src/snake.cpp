#include <iostream>
#include <vector>

#include "snake.hpp"

//-------------------CONSTRUCTORS/DESTRUCTORS-----------------------
SnakeGame::SnakeGame()
{
    snake_length = 0;
    currentScore = 0;

    generateSnake();
    setSnake();
    foodUpdate();

    oldBacktailPos = new SnakeNode(0, 0);

    foodtimer.gameTimerStart();
    modifierTimer.gameTimerStart();
}

SnakeGame::~SnakeGame()
{
    deleteSnake();
}

//-------------------SNAKE_FUNCTIONS----------------------
void SnakeGame::moveSnake()
{
    //Moves the backtail and head of the snake to animate it
    if (gamestate.isInGame())
    {
        SnakeNode *walker = backtail;
        for (int i = 0; i < snake_length; i++)
        {
            if (walker == backtail)
            {
                posHandler.setFree(walker->yValue, walker->xValue);

                oldBacktailPos->yValue = backtail->yValue;
                oldBacktailPos->xValue = backtail->xValue;

                walker->xValue = walker->Next->xValue;
                walker->yValue = walker->Next->yValue;
                walker = walker->Next;
            }
            else if (walker == head)
            {
                posHandler.setSnakeBody(walker->yValue, walker->xValue); //Sets the old position of the head as a bodypart
                moveHeadPosition();                                      //Moves the head's coords to a new position

                foodCheck();      //checks if there's food on the new head-position
                snakeBodyCheck(); //checks if a bodypart is on the new head-position
                modifierCheck();  //checks if there's a modifier on the new head-position

                //Assigns the new position as the head
                posHandler.setSnakeHead(walker->yValue, walker->xValue);

                wallCheck(); //checks for wall-collision

                break;
            }
            else
            {
                walker->xValue = walker->Next->xValue;
                walker->yValue = walker->Next->yValue;

                walker = walker->Next;
            }
        }
    }
}

void SnakeGame::growSnake()
{
    //Uses old tail position to grow the snake by exactly one unit
    SnakeNode *NewBackTail = new SnakeNode(oldBacktailPos->yValue, oldBacktailPos->xValue);
    NewBackTail->Next = backtail;

    backtail = NewBackTail;

    posHandler.setSnakeBody(backtail->yValue, backtail->xValue);

    snake_length++;
    currentScore++;
}

void SnakeGame::moveHeadPosition()
{
    //Moves the snake's head-coordinates depending on state of direction class
    if (direction.isRight())
    {
        head->xValue++;
    }
    else if (direction.isLeft())
    {
        head->xValue--;
    }
    else if (direction.isUp())
    {
        head->yValue--;
    }
    else if (direction.isDown())
    {
        head->yValue++;
    }
}

void SnakeGame::halfSnake()
{
    //Halves snake (modifier)
    SnakeNode *walker = backtail;
    SnakeNode *next = nullptr;
    int half_length = snake_length / 2;

    if (snake_length >= DEFAULT_SNAKE_LENGTH)
    {
        for (int i = 0; i < half_length; i++)
        {
            next = walker->Next;
            posHandler.setFree(walker->yValue, walker->xValue);

            delete walker;

            walker = next;
            backtail = walker;
            snake_length--;
        }
    }
}

//-------------------SET_FUNCTIONS-----------------------
void SnakeGame::setSnake()
{
    //Sets the snake on the playground
    SnakeNode *walker = this->backtail;
    for (int i = 0; i < snake_length; i++)
    {
        if (walker == head)
        {
            posHandler.setSnakeHead(walker->yValue, walker->xValue);
        }
        else
        {
            posHandler.setSnakeBody(walker->yValue, walker->xValue);
        }
        walker = walker->Next;
    }
}
//-------------------------ANIMATION_FUNCTIONS-------------------------
void SnakeGame::refreshPositionSystem(WINDOW *window)
{
    //Refreshes the positionsystem onto the ncurses-window
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            posHandler(y, x)->printItem(window, y, x);
        }
    }
}

void SnakeGame::playerLostSeq(WINDOW *window)
{
    //Sequence which is run when player loses
    posHandler.clearPositionSystem();
    refreshPositionSystem(window);
    highscorehandler.newHighScore(currentScore, window);

    gamestate.setPlayerQuit();
}

//-------------------------GENERATE_FUNCTIONS-------------------------
void SnakeGame::generateSnake()
{
    //Generates the linked list which the snake uses
    int tempX = 45;
    int tempY = 12;
    for (int i = 0; i < DEFAULT_SNAKE_LENGTH; i++)
    {
        SnakeNode *node = new SnakeNode(tempY, tempX);

        if (this->snake_length == 0)
        {
            head = backtail = node;
            snake_length++;
        }
        else
        {
            head->Next = node;
            head = node;
            snake_length++;
        }
        tempX++;
    }
}

//----------------------USER_INPUT_FUNCTIONS------------------------
void SnakeGame::userGameInput(const char &key)
{
    //User input for the game
    char const EXIT = 'q';
    char const UP = 'w';
    char const DOWN = 's';
    char const RIGHT = 'd';
    char const LEFT = 'a';

    switch (key)
    {
    case UP:
        direction.setUp();
        break;
    case DOWN:
        direction.setDown();
        break;
    case LEFT:
        direction.setLeft();
        break;
    case RIGHT:
        direction.setRight();
        break;
    case EXIT:
        gamestate.setPlayerQuit();
        break;
    }
}

//--------------------GET_FUNCTIONS-----------------------------
int SnakeGame::getBoardHeight() const
{
    return BOARD_HEIGHT;
}

int SnakeGame::getBoardWidth() const
{
    return BOARD_WIDTH;
}

int SnakeGame::getGameState() const
{
    return gamestate.getState();
}

int SnakeGame::getCurrentScore() const
{
    return currentScore;
}

int SnakeGame::getGameDifficulty() const
{
    return gameDifficulty.getDifficulty();
}

//---------------------DELETE_FUNCTIONS-------------------------
void SnakeGame::deleteSnake()
{
    //Deletes the snake's nodes
    SnakeNode *walker = backtail;
    SnakeNode *Next = nullptr;
    while (walker != nullptr)
    {
        Next = walker->Next;
        delete walker;
        walker = Next;
    }

    delete oldBacktailPos;
}
//-----------------------CHECK_FUNCTIONS--------------------------

void SnakeGame::wallCheck()
{
    //Checks for wall-collision
    int tempX = head->xValue;
    int tempY = head->yValue;

    if (tempY <= 0 || tempY >= BOARD_HEIGHT - 1 || tempX <= 0 || tempX >= BOARD_WIDTH - 1)
    {
        gamestate.setPlayerLost();
    }
}

void SnakeGame::snakeBodyCheck()
{
    //Checks for body-collision
    int tempX = head->xValue;
    int tempY = head->yValue;

    if (posHandler(tempY, tempX)->isSnakeBody())
    {
        gamestate.setPlayerLost();
    }
}

void SnakeGame::foodCheck()
{
    //Checks for food-collision and food upkeep
    int tempY = head->yValue;
    int tempX = head->xValue;
    if (posHandler(tempY, tempX)->isFood())
    {
        growSnake();
    }

    if (foodtimer.foodUpdateReady())
    {
        foodUpdate();

        foodtimer.gameTimerReset();
    }
}

void SnakeGame::foodUpdate()
{
    //Updates food on a new position
    int foodXvalue = 0;
    int foodYvalue = 0;
    bool foodSet = false;

    while (!foodSet)
    {
        foodXvalue = rand() % (BOARD_WIDTH);
        foodYvalue = rand() % (BOARD_HEIGHT);
        if (posHandler(foodYvalue, foodXvalue)->isFree())
        {
            posHandler.setFood(foodYvalue, foodXvalue);
            foodSet = true;
        }
    }
}

void SnakeGame::modifierCheck()
{
    //Checks for modifier-collision, modifier upkeep and resets modifiers
    int tempY = head->yValue;
    int tempX = head->xValue;
    if (posHandler(tempY, tempX)->isModifier())
    {
        randomModifier();
        modifierInterval.gameTimerStart();
    }

    if (modifierTimer.modifierUpdateReady())
    {
        modifierUpdate();

        modifierTimer.gameTimerReset();
    }

    if (modifierInterval.modifierFinished() && !gameModifier.isNotActive())
    {
        if (gameModifier.isExtremeSpeed())
        {
            gameDifficulty.setNormalDifficulty();
            gameModifier.isNotActive();
        }
        else if (gameModifier.isInvertedControls())
        {
            direction.resetInverted();
            gameModifier.isNotActive();
        }
    }
}

//--------------------------MODIFIER_FUNCTIONS------------------------
void SnakeGame::modifierUpdate()
{
    //Updates modifers on a free position
    int modXvalue = 0;
    int modYvalue = 0;
    bool modSet = false;

    while (!modSet)
    {
        modXvalue = rand() % (BOARD_WIDTH);
        modYvalue = rand() % (BOARD_HEIGHT);
        if (posHandler(modYvalue, modXvalue)->isFree())
        {
            posHandler.setModifier(modYvalue, modXvalue);
            modSet = true;
        }
    }
}

void SnakeGame::randomModifier()
{
    //Randomly chooses a modifier for the player
    int choice = rand() % 3;
    int const HALF_SNAKE = 0;
    int const INVERTED_CONTROLS = 1;
    int const SUPER_SPEED = 2;

    switch (choice)
    {
    case HALF_SNAKE:
        halfSnake();
        break;
    case INVERTED_CONTROLS:
        gameModifier.setInvertedControls();
        direction.setInverted();
        break;
    case SUPER_SPEED:
        gameDifficulty.setExtremeDifficulty();
        gameModifier.setExtremeSpeed();
        break;
    }
}
