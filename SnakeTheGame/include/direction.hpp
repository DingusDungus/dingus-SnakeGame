#ifndef DIRECTION_HPP
#define DIRECTION_HPP

class Direction
{
public:
    Direction() : state(RIGHT), isInverted(false){};

    void setRight()
    {
        if (state != RIGHT && isInverted)
        {
            state = LEFT;
        }
        else if (state != LEFT && !isInverted)
        {
            state = RIGHT;
        }
    }
    void setLeft()
    {
        if (state != RIGHT && !isInverted)
        {
            state = LEFT;
        }
        else if (state != LEFT && isInverted)
        {
            state = RIGHT;
        }
    }
    void setUp()
    {
        if (state != DOWN && !isInverted)
        {
            state = UP;
        }
        else if (state != UP && isInverted)
        {
            state = DOWN;
        }
    }
    void setDown()
    {
        if (state != UP && !isInverted)
        {
            state = DOWN;
        }
        else if (state != DOWN && isInverted)
        {
            state = UP;
        }
    }

    void setInverted()
    {
        isInverted = true;
    }

    void resetInverted()
    {
        isInverted = false;
    }

    bool isRight() const { return state == RIGHT; }
    bool isLeft() const { return state == LEFT; }
    bool isUp() const { return state == UP; }
    bool isDown() const { return state == DOWN; }

private:
    int const RIGHT = 0;
    int const LEFT = 1;
    int const UP = 2;
    int const DOWN = 3;

    int state;

    bool isInverted;
};

#endif