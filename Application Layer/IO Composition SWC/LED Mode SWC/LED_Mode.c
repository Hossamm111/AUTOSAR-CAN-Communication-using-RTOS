/********************************************************************************/
/* Module Name  : LED_Mode.c							*/
/* Author       : Hossam						        */
/* Purpose      : Choose LED Mode				                */
/********************************************************************************/

#include "../../Application SWC/APP.h"

/********************************************************************************/
/* Function Name: void LED_Mode (uint8 Led_State)			        */
/* Inputs       : Led_State		                                        */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Choose LED Mode	                                        */
/********************************************************************************/

void LED_Mode (uint8 Led_State)
{
/*
 * Check the Desired LED State & Switch on that LED. The Available Options are:
 *
 * 1. White
 * 2. Red
 * 3. Blue
 * 4. Green
 * 5. Violet
 * 6. Yellow
 * 7. Cyan
 *
 */
  switch (Led_State)
  {
  case WHITE:
    LED_On(RED_LED);
    LED_On(BLUE_LED);
    LED_On(GREEN_LED);
    break;
    
  case RED:
    LED_On(RED_LED);
    LED_Off(BLUE_LED);
    LED_Off(GREEN_LED);
    break;
    
  case BLUE:
    LED_Off(RED_LED);
    LED_On(BLUE_LED);
    LED_Off(GREEN_LED);
    break;
    
  case GREEN:
    LED_Off(RED_LED);
    LED_Off(BLUE_LED);
    LED_On(GREEN_LED);
    break;
    
  case VIOLET:
    LED_On(RED_LED);
    LED_On(BLUE_LED);
    LED_Off(GREEN_LED);
    break;
    
  case YELLOW:
    LED_On(RED_LED);
    LED_Off(BLUE_LED);
    LED_On(GREEN_LED);
    break;
    
  case CYAN:
    LED_Off(RED_LED);
    LED_On(BLUE_LED);
    LED_On(GREEN_LED);
    break;
  }
}
