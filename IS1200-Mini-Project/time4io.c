 /* 
   File: time4io.c
   Author: Daniel Aspin
   Description: This file contains the implementation of button and switches values.
*/
 
 #include <stdint.h>
 #include <pic32mx.h>
 #include "mipslab.h"


// The switches SW4 through SW1 are connected to bits 11 through 8 of Port D.
 int getsw( void ) {

  return ((PORTD >> 8) & 0x000f);

 }
 
//  The buttons BTN4, BTN3, and BTN2, are connected to bits 7, 6 and 5 of Port D.
 int getbtns( void ) {

  return ((PORTD >> 5) & 0x0007);

 }