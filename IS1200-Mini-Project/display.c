/* 
   File: display.c
   Author: Daniel Aspin and Adalet Adiljan
   Description: This file contains functions related to displaying game elements.
*/

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

uint8_t pixels[512];

/* Author: Daniel Aspin */
void start_counter (void) {
    display_string(0, "3");
    display_string(1, "Use BTN4 to jump");
    display_update();
    delay(1000);
    display_string(0, "2");
    display_string(1, "Use BTN4 to jump");
    display_update();
    delay(1000);
    display_string(0, "1");
    display_string(1, "Use BTN4 to jump");
    display_update();
    display_string(1, "");
    delay(800);
}

/* Author: Daniel Aspin */
void display_turnoff (void) {
    int constant = 0;

    int i, j;
	
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 128; j++)
			pixels[j+(i*128)] = constant;
	}
}


/* Author: Daniel Aspin and Adalet Adiljan */
void set_obstacle (int x, int y) {
    if (x >= 124 || x <= 2) return;

    int i, j;

    for (i = 0; i < 4; i++)
    {
        if (i == y) {
            for (j = 0; j < 128; j++)
            {
                if (j == x) {
                    pixels[j+(i*128)] = 255;
                    pixels[j+(i*128)-1] = 255;
                    pixels[j+(i*128)+1] = 255;
                    
                }
            }
            
        }
    }
    
}

/* Author: Daniel Aspin and Adalet Adiljan */
void set_bird (int x, int y) {

    int i, j;

    for (i = 0; i < 4; i++)
    {
        if (i == y) {
            for (j = 0; j < 128; j++)
            {
                if (j == x) {

                    pixels[j+(i*128)] = bird_pixel_value;

                }
            }
            
        }
    }
    
}