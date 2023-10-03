#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

// Define the dimensions of the game board
int height = 25, width = 50;

// Variables for snake and food position, direction, game state, and score
int i, j, snake_x, snake_y, food_x, food_y, direction;
int game_over, score;

// Function to draw the game board
void draw_board()
{
    clear(); // Clear the screen

    // Print the player's score at the top of the screen
    printw("Score: %d\n", score);

    // Loop to draw the game board
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // Draw walls with '#' characters
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                printw("#");
            }
            else
            {
                // Draw the snake as '0', food as '*', and empty space as ' '
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
        printw("\n"); // Move to the next line
    }

    refresh(); // Refresh the screen to display the changes
}

// Function to set up the game
void set_up_game()
{
    srand(time(NULL)); // Reset the random number generator
    game_over = 0;     // Initialize the game state
    score = 0;         // Initialize the score

    // Initialize the snake's starting position and the initial food position
    snake_x = height / 2;
    snake_y = width / 2;
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
            direction = 1; // Move snake up
            break;
        case KEY_LEFT:
            direction = 2; // Move snake left
            break;
        case KEY_RIGHT:
            direction = 3; // Move snake right
            break;
        case KEY_DOWN:
            direction = 4; // Move snake down
            break;
        case 'q':
            game_over = 1; // Quit the game
            break;
        default:
            break;
        }
    }
}

// Function to control the game logic
void controller()
{
    usleep(20000000000000); // Delay to control game speed

    switch (direction)
    {
    case 1:
        snake_x--; // Move snake up
        break;
    case 2:
        snake_y--; // Move snake left
        break;
    case 3:
        snake_y++; // Move snake right
        break;
    case 4:
        snake_x++; // Move snake down
        break;
    default:
        break;
    }

    // Check for collision with walls
    if (snake_x == 0 || snake_x == height - 1 || snake_y == 0 || snake_y == width - 1)
    {
        game_over = 1; // Set game over if the snake hits a wall
    }

    // Check for collision with food
    if (abs(snake_x - food_x) <= 1 && abs(snake_y - food_y) <= 1)
    {
        score++;                            // Increase the score
        food_x = rand() % (height - 2) + 1; // Generate a new random food position
        food_y = rand() % (width - 2) + 1;
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
    while (!game_over)
    {
        draw_board(); // Draw the game board
        input();      // Handle player input
        controller(); // Control game logic
    }

    endwin(); // Clean up and close the NCurses library
    return 0;
}
