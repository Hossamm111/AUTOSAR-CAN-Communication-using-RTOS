/********************************************************************************/
/* Module Name  : GPT.c							        */
/* Author       : Hossam						        */
/* Purpose      : Use GPT Services						*/
/********************************************************************************/

#include "GPT.h"

/********************************************************************************/
/* Function Name: void GPT_Init (void)					        */
/* Inputs       : None		                                                */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initialize GPT Timers	 				        */
/********************************************************************************/

void GPT_Init (void)
{
  /*                                    
  *                             *
  *     Timer 0 Initialization  *
  *                             *
  */                                    
  
  /*
  * Enable the Timer 0 peripheral
  */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  
  /*
  * Wait for the Timer 0 module to be ready
  */
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}
  
  /*
  *  Configure Timer 0 as a full-width periodic timer
  */
  TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  
  /*
  *  Set the count time for timer A
  */
  TimerLoadSet(TIMER0_BASE, TIMER_A, (Timer0_Load));
  
  /*
  *  Register Timer0_Handler as the handler function for the timer interrupt
  */
  TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0_Handler);
  
  /*
  *  Enable the interrupt source for timer 0
  */
  TimerIntEnable(TIMER0_BASE, (TIMER_CAPA_EVENT | TIMER_TIMA_TIMEOUT));
  
  /*
  * Enable timer 0
  */
  TimerEnable(TIMER0_BASE, TIMER_A);
  
  /*                                    
  *                             *
  *     Timer 1 Initialization  *
  *                             *
  */
  
  /*
  * Enable the Timer 1 peripheral
  */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
  
  /*
  * Wait for the Timer 1 module to be ready
  */
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)){}
  
  /*
  *  Configure Timer 1 as a full-width periodic timer
  */
  TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
  
  /*
  *  Set the count time for timer A
  */
  TimerLoadSet(TIMER1_BASE, TIMER_A, Timer1_Load);
  
  /*
  *  Register Timer1_Handler as the handler function for the timer interrupt
  */
  TimerIntRegister(TIMER1_BASE, TIMER_A, Timer1_Handler);
  
  /*
  *  Enable the interrupt source for timer 1
  */
  TimerIntEnable(TIMER1_BASE, (TIMER_CAPA_EVENT | TIMER_TIMA_TIMEOUT));
  
  /*
  * Enable timer 1
  */
  TimerEnable(TIMER1_BASE, TIMER_A);
}

/********************************************************************************/
/* Function Name: void Timer0_Handler (void)					*/
/* Inputs       : None		                                                */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Handler for Master mc	 				        */
/********************************************************************************/

void Timer0_Handler (void)
{
  TimerIntClear(TIMER0_BASE, (TIMER_CAPA_EVENT | TIMER_TIMA_TIMEOUT));
}

/********************************************************************************/
/* Function Name: void Timer1_Handler (void)					*/
/* Inputs       : None		                                                */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Handler for Slave mc	 				        */
/********************************************************************************/

void Timer1_Handler (void)
{
  TimerIntClear(TIMER1_BASE, (TIMER_CAPA_EVENT | TIMER_TIMA_TIMEOUT));
}
