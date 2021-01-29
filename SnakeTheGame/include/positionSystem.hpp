#ifndef POSITION_SYSTEM_HPP
#define POSITION_SYSTEM_HPP

#include <ncurses.h>

class PositionSystem
{
public:
    virtual ~PositionSystem() {}

    //------------------GAME_FUNCTIONS--------------------
    void virtual printItem(WINDOW *window, int const &y, int const &x) const = 0;

    bool virtual isFood() const { return false; }

    bool virtual isFree() const { return false; }

    bool virtual isWall() const { return false; }

    bool virtual isSnakeBody() const { return false; }

    bool virtual isModifier() const { return false; }
};

class Free : public PositionSystem
{
public:
    void printItem(WINDOW *window, int const &y, int const &x) const override
    {
        mvwprintw(window, y, x, " ");
    }

    bool isFree() const override { return true; }
};

//----------------------------------GAME_ITEMS----------------------------
class Wall : public PositionSystem
{
public:
    void printItem(WINDOW *window, int const &y, int const &x) const override
    {
        mvwprintw(window, y, x, "#");
    }

    bool isWall() const override { return true; }
};

class SnakeBody : public PositionSystem
{
public:
    void printItem(WINDOW *window, int const &y, int const &x) const override
    {
        mvwprintw(window, y, x, "+");
    }

    bool isSnakeBody() const override { return true; }
};

class SnakeHead : public PositionSystem
{
public:
    void printItem(WINDOW *window, int const &y, int const &x) const override
    {
        mvwprintw(window, y, x, "o");
    }
};

class Food : public PositionSystem
{
public:
    void printItem(WINDOW *window, int const &y, int const &x) const override
    {
        mvwprintw(window, y, x, "@");
    }

    bool isFood() const override { return true; }
};

class Modifier : public PositionSystem
{
public:
    void printItem(WINDOW *window, int const &y, int const &x) const override
    {
        mvwprintw(window, y, x, "?");
    }

    bool isModifier() const override { return true; }
};

#endif