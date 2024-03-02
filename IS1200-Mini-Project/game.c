/* 
   File: game.c
   Author: Daniel Aspin and Adalet Adiljan
   Description: This file contains the implementation of the game logic.
*/

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int obstacles_offset = 30;
int num_obstacles = 25;

int bird_x_pos = 25;
int bird_y_pos = 1;

int bird_pixel_value = 128;

/* Author: Daniel Aspin and Adalet Adiljan */
void createObstacles (int obstacles_decrement) {
    int i;

    for (i = 0; i < num_obstacles; i++)
    {
        set_obstacle((30 * i) + 100 - obstacles_decrement, 0);
        // Modulo operation for variation on obstacles
        set_obstacle((30 * i) + 100 - obstacles_decrement, i % 3);
        set_obstacle((30 * i) + 100 - obstacles_decrement, 3);
    }
    
}

/* Author: Daniel Aspin */
void jumpOrFall (int buttons) {

    // BTN4 (100)
    if(buttons & 4)
    {
        // Logic for jump
        if (bird_pixel_value == 1)
        {
            if (bird_y_pos == 0)
            {
                bird_y_pos = 0;
                bird_pixel_value = 2;
            } else{
                bird_y_pos--;
                bird_pixel_value = 128;
            }
            
        }
        bird_pixel_value = (bird_pixel_value / 2);
    } else {
        // Logic for fall
        if (bird_pixel_value == 128)
        {
            if (bird_y_pos == 3)
            {
                bird_y_pos = 3;
                bird_pixel_value = 64;
            } else{
                bird_y_pos++;
                bird_pixel_value = 1;
            }
            
        }
        bird_pixel_value = (bird_pixel_value * 2);
    }
}

/* Author: Daniel Aspin */
void detectCollision (void) {

    /* This is for obstacles only on y equals to 0 and 3 */
    /*
    if (bird_y_pos == 3 || bird_y_pos == 0)
    {
        if (pixels[25] == 255 || pixels[409] == 255)
        {
            gameOver();
            resetGame();
        }
        
    }*/

    /* This is for obstacles with all y values */
    int obstacles_positions[] = {26, 154, 282, 410};

    if (pixels[obstacles_positions[bird_y_pos]] == 255) {
        gameOver();
        resetGame();
    }
    
}

/* Author: Daniel Aspin */
void checkWin (void) {
    int j;
    int sumrow = 0;

    for (j = 0; j < 128; j++)
    {
        sumrow += pixels[j];
    }

    // 200 is a random number between 1 and 255
    if (sumrow < 200)
    {
        display_turnoff();
        display_string(0, "You Win!");
        display_update();
        delay(1000);
        resetGame();
    }
    
    
}

/* Author: Daniel Aspin */
void resetGame (void) {
    obstacles_decrement = 0;
    bird_x_pos = 25;
    bird_y_pos = 1;
    bird_pixel_value = 128;

}

/* Author: Daniel Aspin */
void gameOver (void) {
    display_turnoff();
    display_string(0, "Game Over!");
    display_update();
    delay(1000);
}