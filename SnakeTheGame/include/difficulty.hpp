#ifndef DIFFICULTY_HPP
#define DIFFICULTY_HPP

class Difficulty
{
public:
    static int const EASY_DIFFICULTY = 150;
    static int const NORMAL_DIFFICULTY = 70;
    static int const HARD_DIFFICULTY = 50;
    static int const EXTREME_DIFFICULTY = 40;

    Difficulty() { state = NORMAL_DIFFICULTY; }

    void setEasyDifficulty() { state = EASY_DIFFICULTY; }
    void setHardDifficulty() { state = HARD_DIFFICULTY; }
    void setExtremeDifficulty() { state = EXTREME_DIFFICULTY; }
    void setNormalDifficulty() { state = NORMAL_DIFFICULTY; }

    int getDifficulty() const { return state; }

private:
    int state;
};

#endif