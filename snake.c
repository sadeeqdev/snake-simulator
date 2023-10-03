#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

int height = 25, width = 50;
int i, j, snake_x, snake_y, food_x, food_y, direction;
int game_over, score;

void draw_board()
{
    clear();
    printw("Score: %d\n", score);

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                printw("#");
            }
            else
            {
                if (i == snake_x && j == snake_y)
                {
                    printw("0");
                }
                else if (i == food_x && j == food_y)
                {
                    printw("*");
                }
                else
                {
                    printw(" ");
                }
            }
        }
        printw("\n");
    }

    refresh();
}

void set_up_game()
{
    srand(time(NULL)); // resets the random number generator
    game_over = 0;
    score = 0;
    snake_x = height / 2;
    snake_y = width / 2;
    food_x = rand() % (height - 2) + 1;
    food_y = rand() % (width - 2) + 1;
}

void input()
{
    int ch = getch();

    if (ch != ERR)
    {
        switch (ch)
        {
        case KEY_UP:
            direction = 1;
            break;
        case KEY_LEFT:
            direction = 2;
            break;
        case KEY_RIGHT:
            direction = 3;
            break;
        case KEY_DOWN:
            direction = 4;
            break;
        case 'q':
            game_over = 1;
            break;
        default:
            break;
        }
    }
}

void controller()
{
    usleep(100000);
    switch (direction)
    {
    case 1:
        snake_x--;
        break;
    case 2:
        snake_y--;
        break;
    case 3:
        snake_y++;
        break;
    case 4:
        snake_x++;
        break;
    default:
        break;
    }

    if (snake_x == 0 || snake_x == height - 1 || snake_y == 0 || snake_y == width - 1)
    {
        game_over = 1;
    }

    if (abs(snake_x - food_x) <= 1 && abs(snake_y - food_y) <= 1)
    {
        score++;
        food_x = rand() % (height - 2) + 1;
        food_y = rand() % (width - 2) + 1;
    }
}

int main()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    set_up_game();
    while (!game_over)
    {
        draw_board();
        input();
        controller();
    }

    endwin();
    return 0;
}
