/********************************************************************************/
/* Module Name  : OS.c							        */
/* Author       : Hossam						        */
/* Purpose      : Operating System Service				        */
/********************************************************************************/

#include "OS.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

void (*Task1)(void), (*Task2)(void);

uint16 Task1_Periodicity, Task2_Periodicity;

/********************************************************************************/
/* Function Name: void Create_Task1 (void (*Function)(void), uint16 Cycles)	*/
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Create a Task	                                                */
/********************************************************************************/

void Create_Task1 (void (*Function)(void), uint16 Cycles)
{
/*
 * Create the First Task & Assign its Periodicity
 */
  Task1 = Function;
  
  Task1_Periodicity = Cycles;
}

/********************************************************************************/
/* Function Name: void Create_Task2 (void (*Function)(void),uint16 Cycles)	*/
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Create a Task	                                                */
/********************************************************************************/

void Create_Task2 (void (*Function)(void),uint16 Cycles)
{
/*
 * Create the Second Task & Assign its Periodicity
 */
  Task2 = Function;
  
  Task2_Periodicity = Cycles;
}

/********************************************************************************/
/* Function Name: void Scheduler (void)			                        */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Go to a Task Based on its Periodicity	                        */
/********************************************************************************/

void Scheduler (void)
{
  static uint32 Tick_Timer = ZERO;
  
  Tick_Timer++;
  
/*
 * Check the Tick Timer & Execute the Correct Task based on the Task Periodicities
 */
  if (Tick_Timer >= Task1_Periodicity)
    
    Task1();
  
  if (Tick_Timer >= Task2_Periodicity)
  {
    Task2();
    
    Tick_Timer = ZERO;
  }
}

/********************************************************************************/
/* Function Name: void Scheduler_Start (void)			                */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Start the Scheduler & the Timer	                        */
/********************************************************************************/

void Scheduler_Start (void)
{
/*
 * Start the Scheduler & the Timer
 */
  Set_Scheduler(Scheduler);
  
  Timer_Enable();
}




