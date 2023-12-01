/**************************************************************************************************
* Brickeye                                                                       Copyright (C) 2022
***************************************************************************************************
* Program:     Main.c
* Description: Main program loop
**************************************************************************************************/

// Include Dependencies
#include "TOASTER_NUCLEOF446RE.h"
#include "APP.h"


/**************************************************************************************************
* Main Program Loop
**************************************************************************************************/
int main(void)
{
   // Initialize the chip
   Chip_Init();

   // Initialize the application
   App_Init();


   /* Replace with your application code */
   while (1)
   {
      // call chip level routines that need updating
      Chip_Update();

      // call application
      App_Update();
   }

}
