#include "positionHandler.hpp"

positionHandler::positionHandler()
{
    freePosition = new Free;
    wallPosition = new Wall;
    bodyPosition = new SnakeBody;
    headPosition = new SnakeHead;
    foodPosition = new Food;
    modPosition = new Modifier;

    positionSystem = new PositionSystem **[BOARD_HEIGHT];
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        positionSystem[y] = new PositionSystem *[BOARD_WIDTH];
    }

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (x != 0 && x != BOARD_WIDTH - 1 && y != 0 && y != BOARD_HEIGHT - 1)
            {
                positionSystem[y][x] = freePosition;
            }
            else
            {
                positionSystem[y][x] = wallPosition;
            }
        }
    }
}

positionHandler::~positionHandler()
{
    delete freePosition;
    delete wallPosition;
    delete bodyPosition;
    delete headPosition;
    delete modPosition;
    delete foodPosition;

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            positionSystem[y][x] = nullptr;
        }
        delete[] positionSystem[y];
    }
    delete[] positionSystem;
    positionSystem = nullptr;
}

PositionSystem *positionHandler::operator()(int const &y, int const &x)
{
    return positionSystem[y][x];
}

void positionHandler::clearPositionSystem()
{
    //Clears the positionsystem into it's default state
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (x != 0 && x != BOARD_WIDTH - 1 && y != 0 && y != BOARD_HEIGHT - 1)
            {
                if (!positionSystem[y][x]->isFree())
                {
                    setFree(y, x);
                }
            }
            else
            {
                if (!positionSystem[y][x]->isWall())
                {
                    setWall(y, x);
                }
            }
        }
    }
}

void positionHandler::setFree(const int &y, const int &x)
{
    //Sets given position to Free
    positionSystem[y][x] = this->freePosition;
}

void positionHandler::setSnakeBody(const int &y, const int &x)
{
    //Sets given position to Snakebody
    positionSystem[y][x] = this->bodyPosition;
}

void positionHandler::setSnakeHead(const int &y, const int &x)
{
    //Sets given position to snakehead
    positionSystem[y][x] = this->headPosition;
}

void positionHandler::setWall(const int &y, const int &x)
{
    //Sets given position to wall
    positionSystem[y][x] = this->wallPosition;
}

void positionHandler::setFood(const int &y, const int &x)
{
    //Sets given position to food
    positionSystem[y][x] = this->foodPosition;
}

void positionHandler::setModifier(const int &y, const int &x)
{
    //Sets given position to modifier
    positionSystem[y][x] = this->modPosition;
}
