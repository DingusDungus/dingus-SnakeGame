#ifndef POSITION_HANDLER_HPP
#define POSITION_HANDLER_HPP

#include "positionSystem.hpp"
#include <vector>

class positionHandler
{
public:
    positionHandler();
    ~positionHandler();

    void setFree(const int &y, const int &x);
    void setSnakeBody(const int &y, const int &x);
    void setSnakeHead(const int &y, const int &x);
    void setWall(const int &y, const int &x);
    void setFood(const int &y, const int &x);
    void setModifier(const int &y, const int &x);

    void clearPositionSystem();

    PositionSystem *operator()(int const& y, int const& x);

private:
    PositionSystem ***positionSystem;

    Free* freePosition;
    Wall* wallPosition;
    SnakeBody* bodyPosition;
    SnakeHead* headPosition;
    Food* foodPosition;
    Modifier* modPosition;

    int const BOARD_HEIGHT = 25;
    int const BOARD_WIDTH = 100;

};

#endif