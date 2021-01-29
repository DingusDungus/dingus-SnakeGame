#ifndef GAME_MODIFIER_HPP
#define GAME_MODIFIER_HPP

class GameModifier
{
public:
    //Handles modifiers which are active in a timed duration
    GameModifier() { state = NOT_ACTIVE; }

    void setNotActive() { state = NOT_ACTIVE; }
    void setInvertedControls() { state = INVERTED_CONTROLS; }
    void setExtremeSpeed() { state = EXTREME_SPEED; }

    bool isNotActive() const { return state == NOT_ACTIVE; }
    bool isInvertedControls() const { return state == INVERTED_CONTROLS; }
    bool isExtremeSpeed() const { return state == EXTREME_SPEED; }

private:
    int const NOT_ACTIVE = 0;
    int const INVERTED_CONTROLS = 1;
    int const EXTREME_SPEED = 3;

    int state;
};

#endif