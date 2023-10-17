#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

// Define the dimensions of the game board
int height = 30, width = 50;

// Variables for snake and food position, direction, game state, and score
int *snake_x, *snake_y, snake_length;
int food_x, food_y, direction;
int game_over, score;

// Function to draw the game board
void draw_board()
{
    clear(); // Clear the screen

    // Draw the snake
    for (int i = 0; i < snake_length; i++)
    {
        mvaddch(snake_x[i], snake_y[i], '0');
    }

    // Draw the food
    mvaddch(food_x, food_y, '*');

    // Draw the walls
    for (int i = 0; i < height; i++)
    {
        mvaddch(i, 0, '#');
        mvaddch(i, width - 1, '#');
    }
    for (int j = 0; j < width; j++)
    {
        mvaddch(0, j, '#');
        mvaddch(height - 1, j, '#');
    }

    // Display score
    mvprintw(0, width + 1, "Score: %d", score);

    // Display game over message if the game is over
    if (game_over)
    {
        mvprintw(height / 2, (width - 24) / 2, "Game Over! Press 'R' to replay or 'Q' to quit.");
    }

    refresh(); // Refresh the screen to display the changes
}

// Function to set up the game
void set_up_game()
{
    srand(time(NULL)); // Reset the random number generator
    game_over = 0;     // Initialize the game state
    score = 0;         // Initialize the score

    // Initialize the snake's starting position and length
    snake_length = 1;
    snake_x = (int *)malloc(sizeof(int) * height * width);
    snake_y = (int *)malloc(sizeof(int) * height * width);
    snake_x[0] = height / 2;
    snake_y[0] = width / 2;

    // Initialize the initial food position
    food_x = rand() % (height - 2) + 1;
    food_y = rand() % (width - 2) + 1;
}

// Function to handle player input
void input()
{
    int ch = getch(); // Get a character from the user's input

    if (ch != ERR) // Check if a character was input
    {
        switch (ch)
        {
        case KEY_UP:
            if (direction != 4) // Prevent moving directly opposite
                direction = 1;  // Move snake up
            break;
        case KEY_LEFT:
            if (direction != 3)
                direction = 2; // Move snake left
            break;
        case KEY_RIGHT:
            if (direction != 2)
                direction = 3; // Move snake right
            break;
        case KEY_DOWN:
            if (direction != 1)
                direction = 4; // Move snake down
            break;
        case 'q':
            game_over = 1; // Quit the game
            break;
        case 'r':
            if (game_over)
            {
                // Replay the game
                free(snake_x);
                free(snake_y);
                set_up_game();
                game_over = 0;
            }
            break;
        default:
            break;
        }
    }
}

// Function to control the game logic
void controller()
{
    usleep(150000); // Delay to control game speed

    int prev_x = snake_x[0];
    int prev_y = snake_y[0];
    int prev2_x, prev2_y;

    // Move the head of the snake
    switch (direction)
    {
    case 1:
        snake_x[0]--; // Move snake up
        break;
    case 2:
        snake_y[0]--; // Move snake left
        break;
    case 3:
        snake_y[0]++; // Move snake right
        break;
    case 4:
        snake_x[0]++; // Move snake down
        break;
    default:
        break;
    }

    // Check for collision with walls
    if (snake_x[0] == 0 || snake_x[0] == height - 1 || snake_y[0] == 0 || snake_y[0] == width - 1)
    {
        game_over = 1; // Set game over if the snake hits a wall

        return;
    }

    // Check for collision with food
    if (snake_x[0] == food_x && snake_y[0] == food_y)
    {
        score++; // Increase the score

        // Generate new food position
        food_x = rand() % (height - 2) + 1;
        food_y = rand() % (width - 2) + 1;

        // Increase the length of the snake
        snake_length++;
        snake_x = (int *)realloc(snake_x, sizeof(int) * snake_length);
        snake_y = (int *)realloc(snake_y, sizeof(int) * snake_length);

        // Move the rest of the snake
        for (int i = snake_length - 1; i > 0; i--)
        {
            snake_x[i] = snake_x[i - 1];
            snake_y[i] = snake_y[i - 1];
        }
    }

    // Move the rest of the snake
    for (int i = 1; i < snake_length; i++)
    {
        prev2_x = snake_x[i];
        prev2_y = snake_y[i];
        snake_x[i] = prev_x;
        snake_y[i] = prev_y;
        prev_x = prev2_x;
        prev_y = prev2_y;
    }
}

int main()
{
    initscr();             // Initialize the NCurses library
    noecho();              // Disable echoing of input characters
    cbreak();              // Enter cbreak mode to receive key presses without Enter
    curs_set(0);           // Hide the cursor
    keypad(stdscr, TRUE);  // Enable the use of special keys
    nodelay(stdscr, TRUE); // Make getch non-blocking

    set_up_game(); // Initialize the game

    // Main game loop
    while (1)
    {
        draw_board(); // Draw the game board
        input();      // Handle player input
        controller(); // Control game logic

        if (game_over)
        {
            // Display replay or exit options
            int choice;
            mvprintw(height / 2 + 2, (width - 30) / 2, "Press 'R' to replay or 'Q' to quit:");
            while (1)
            {
                choice = getch();
                if (choice == 'r' || choice == 'R')
                {
                    // Replay the game
                    free(snake_x);
                    free(snake_y);
                    set_up_game();
                    game_over = 0;
                    break;
                }
                else if (choice == 'q' || choice == 'Q')
                {
                    // Quit the game
                    endwin(); // Clean up and close the NCurses library
                    free(snake_x);
                    free(snake_y);
                    return 0;
                }
            }
        }
    }
}
