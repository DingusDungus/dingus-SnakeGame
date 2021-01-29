#include <fstream>
#include <sstream>
#include <iostream>
#include "HighscoreHandler.hpp"

HighscoreHandler::HighscoreHandler()
{
    getList();
    sortHighscores();
}

HighscoreHandler::~HighscoreHandler()
{
    writeList();
}

void HighscoreHandler::getList()
{
    //Gets list from file and inserts it into class-vector
    std::ifstream file("HighscoreList.txt");
    std::string line;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            int score = 0;
            std::string number_as_string;
            std::string NewName;
            std::stringstream stream(line);

            stream >> NewName;
            stream >> number_as_string;

            score = std::stoi(number_as_string);

            scoreNode playerScore(NewName, score);

            HighScoreList.push_back(playerScore);
        }
        file.close();
    }
}

void HighscoreHandler::writeList() const
{
    //Writes updated (or not) list into the file 
    int const max_list_size = 10;
    std::ofstream file("HighscoreList.txt");
    for (int i = 0; i < HighScoreList.size() && i < max_list_size; i++)
    {
        file << HighScoreList[i].Name << " " << HighScoreList[i].HighScore << "\n";
    }
    file.close();
}

void HighscoreHandler::HighscoreUI(WINDOW *window) const
{
    //UI for when the player has not achieved a new highscore
    nodelay(window, false);
    mvwprintw(window, 21, 30, "Press any key to continue...");

    wgetch(window);
    nodelay(window, true);
}

void HighscoreHandler::printHighScores(WINDOW *window, int const &currentScore) const
{
    //Prints highscores (and player's current score) out on the ncurses-window
    int const max_list_size = 10;
    int middle_y = 10;
    int const middle_x = 30;

    mvwprintw(window, middle_y - 4, middle_x, "You've lost! Your score was %d", currentScore);
    mvwprintw(window, middle_y - 2, middle_x, "HIGHSCORES");

    for (int i = 0; i < HighScoreList.size() && i < max_list_size; i++)
    {
        mvwprintw(window, middle_y, middle_x, "%s : %d", HighScoreList[i].Name.c_str(), HighScoreList[i].HighScore);
        middle_y++;
    }
}

void HighscoreHandler::sortHighscores()
{
    //Sorts highscores in the vector through insertion sort
    int j = 0;
    scoreNode current;

    for (int i = 0; i < HighScoreList.size(); i++)
    {
        j = i;

        while (j > 0 && HighScoreList[j].HighScore > HighScoreList[j - 1].HighScore)
        {
            current = HighScoreList[j];
            HighScoreList[j] = HighScoreList[j - 1];
            HighScoreList[j - 1] = current;
            j--;
        }
    }
}

void HighscoreHandler::newScoreSequence(int const &newScore, WINDOW *window)
{
    //Sequence run if player achieves a new highscore
    echo();
    nodelay(window, false);
    int const y_value = 22;
    int x_value = 61;
    std::string newName;
    char nameChar[11];

    mvwprintw(window, 21, 30, "You've made it to the highscores! What's your name?");
    mvwprintw(window, 22, 30, "Name (max 10 characters long): ");

    wrefresh(window);

    mvwgetnstr(window, y_value, x_value, nameChar, 10);

    newName = nameChar;

    nameCheck(newName);

    scoreNode newHighScore(newName, newScore);

    HighScoreList.push_back(newHighScore);

    sortHighscores();
}

void HighscoreHandler::newHighScore(int newScore, WINDOW *window)
{
    //Public function used to decide if given score is a highscore or not
    //also calls necessary functions for those two outcomes
    int const max_list_size = 10;

    printHighScores(window, newScore);
    if (HighScoreList.size() >= max_list_size)
    {
        if (newScore > HighScoreList.back().HighScore)
        {

            newScoreSequence(newScore, window);
        }
        else
        {
            HighscoreUI(window);
        }
    }
    else
    {
        newScoreSequence(newScore, window);
    }
}

void HighscoreHandler::nameCheck(std::string &newName) const
{
    //Checks if name is valid to fight future crashes with the getList() function
    if (newName.empty())
    {
        newName = "Nameless";
    }
    else
    {
        for (const char &element : newName)
        {
            if (element == ' ')
            {
                newName = "Nameless";
                break;
            }
        }
    }
}
