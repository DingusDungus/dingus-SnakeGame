#include <thread>

#include "snake.hpp"

using namespace std::literals::chrono_literals;

int main()
{
    SnakeGame snake;
    char key = ' ';

    initscr();
    noecho();
    curs_set(0);

    WINDOW *window = newwin(snake.getBoardHeight() + 1, snake.getBoardWidth(), 0, 0);
    refresh();

    nodelay(window, true);
    snake.refreshPositionSystem(window);

    while (snake.getGameState() != GameState::PLAYER_QUIT)
    {
        if (snake.getGameState() == GameState::IN_GAME)
        {
            snake.moveSnake();
            snake.refreshPositionSystem(window);
            wrefresh(window);
            key = wgetch(window);
            snake.userGameInput(key);

            mvwprintw(window, snake.getBoardHeight(), 0, "Score: %d", snake.getCurrentScore());
        }
        else if (snake.getGameState() == GameState::PLAYER_LOST)
        {
            snake.playerLostSeq(window);
        }

        flushinp();
        std::this_thread::sleep_for(std::chrono::milliseconds(snake.getGameDifficulty()));
    }
    endwin();
    curs_set(3);
}