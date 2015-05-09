/**
 *  pset3 - breakout.c
 *  Darren O'Connor
 *  @mellowdrifter
 *
 *  Simple version of breakout
 */

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle size
#define PHEIGHT 10
#define PWIDTH 60

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // show zero score at first
    updateScoreboard(window, label, points);
    
    // initial velocity
    double x_velocity = 0.5 + drand48();
    double y_velocity = 1.0;

    // Wait for user to click to start
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {   
        //printf("Brick count = %i\n", bricks);
        //printf("Y = %f.02\n", (getY(ball)));
        
        /* COLLISION TIME */
        
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            // If collision in lower half of screen, it must be the paddle
            // A bit messy this, but it works!
            // revisit later to take angles into account!
            if (strcmp(getType(object), "GRect") == 0 && getY(ball) > HEIGHT / 2)
            {
                y_velocity = -y_velocity;
            }
            
            // otherwise it's a brick, which should be removed!
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                bricks--;
                y_velocity = -y_velocity;
                points += 1;
                updateScoreboard(window, label, points); 
            }
        }
    
        /* BALL CONFIG */
        
        // move the ball
        move(ball, x_velocity, y_velocity);
        
        // pause a bit otherwise ball moves way too fast
        pause(4);
        
        // Bouncing off the walls
        if (getX(ball) + getWidth(ball) >= getWidth(window) || (getX(ball) <= 0))
        {
            x_velocity = -x_velocity;
        }
        
        // Bounce off top wall
        else if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
        
        // Lose a life
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            waitForClick();
            
            // Reset ball location
            setLocation(ball, (WIDTH - RADIUS) / 2, (HEIGHT - RADIUS) / 2);
        }
        
        
        /* PADDLE CONFIG */
        
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we hear one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows mouse on x axis
                double x = getX(event) - getWidth(paddle) / 2;
                
                if (x > 0 && (x + PWIDTH) < WIDTH)
                // ensure paddle doesn't go off either edge
                {
                    setLocation(paddle, x, HEIGHT - 30);
                }
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // array of colours to iterate through
    char* colours[] = {"RED", "ORANGE", "YELLOW", "GREEN", "BLUE"};
    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
        //(x, y, width, height)
        // revisit these numbers so can dynamically adjust size for bigger play area
        GRect brick = newGRect( (j * 40) + 2 , (i * 15) + 30, 34, 10);
        setFilled(brick, true);
        setColor(brick, colours[i]);
        add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{    
      GOval ball = newGOval((WIDTH - RADIUS) / 2, (HEIGHT - RADIUS) / 2, RADIUS * 2, RADIUS * 2);
      setFilled(ball, true);
      setColor(ball, "RED");
      add(window, ball);
      return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Paddle size determined by constants. Ensure in the middle by
    // taking note of paddle width itself
    GRect paddle = newGRect((WIDTH - PWIDTH) / 2, HEIGHT - 30, PWIDTH, PHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLUE");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel score = newGLabel("0");
    setFont(score, "SansSerif-36");
    add(window, score);
    
    return score;
    
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
