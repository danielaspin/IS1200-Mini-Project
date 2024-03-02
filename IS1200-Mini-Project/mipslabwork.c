/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2024-02-29 by Daniel Aspin and Adalet Adiljan 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

volatile int *port_E = (volatile int*) 0xbf886110; // Address of PORTE register

// Declare global variables
int timeoutcount = 0;
int obstacles_decrement = 0;

/* Interrupt Service Routine */
void user_isr( void )
{
  // IF TIMEOUT TIMER2
  if(IFS(0) & 0x100)
  {
    display_turnoff();
    timeoutcount++;
    if (timeoutcount == 1)
    { 
      int btns = getbtns();
      jumpOrFall(btns);
      createObstacles(obstacles_decrement);
      set_bird(bird_x_pos, bird_y_pos);
      checkWin();
      detectCollision();
      
      timeoutcount = 0;
      obstacles_decrement++;
      display_image(0, pixels);
    }
    IFSCLR(0) = 0x100;
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // TASK 1
  volatile int *tris_E = (volatile int*) 0xbf886100; // Address of TRISE register
  *tris_E &= ~0xff; // Set PORTE[0-7] to outputs, leaving the other bits unchanged.
  *port_E = 0x0; // Set PORTE to 0.
  TRISD |= 0x0fe0;  // Set TRISD[5-11] to inputs

  // TASK 2
  T2CON = 0;  // Turn off timer2 before configuring it.
  T2CONSET = 0x70;  // Set prescale
  TMR2 = 0x0; // Reset the counter  
  PR2 = ((80000000 / 256) / 10);  // Set period register
  T2CONSET = 0x8000;  // Start the timer

  // TASK 3
  IECSET(0) = 0x100;
  IPCSET(2) = 0x1f;

  start_counter();
  

  enable_interrupt(); // Enables interrupt globally

}

/* This function is called repetitively from the main program */
void labwork( void )
{

}
