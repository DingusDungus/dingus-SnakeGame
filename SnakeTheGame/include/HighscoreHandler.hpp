#ifndef HIGH_SCORE_HANDLER
#define HIGH_SCORE_HANDLER

#include <vector>
#include <string>
#include <ncurses.h>

class HighscoreHandler
{
public:
    //Handles highscores
    HighscoreHandler();
    ~HighscoreHandler();

    void newHighScore(int newScore, WINDOW *window);

private:
    void getList();
    void writeList() const;
    void sortHighscores();
    void printHighScores(WINDOW *window, int const& currentScore) const;
    void nameCheck(std::string &newName) const;
    void HighscoreUI(WINDOW *window) const;
    void newScoreSequence(int const& newScore, WINDOW* window);
    std::string getName(WINDOW *window) const;

    struct scoreNode
    {
        std::string Name;
        int HighScore;

        scoreNode(std::string Name, int HighScore) : Name(Name), HighScore(HighScore) {}

        scoreNode() : Name(""), HighScore(0) {}
    };

    std::vector<scoreNode> HighScoreList;
};

#endif
