/********************************************************************************/
/* Module Name  : Systick_Cfg.h						        */
/* Author       : Hossam				        		*/
/* Purpose      : Configuration file for SysTick Timer Driver		        */
/********************************************************************************/

#ifndef __Systick_Cfg_H__
#define __Systick_Cfg_H__

/*******************************************************************************
 *                           SysTick Reload Configuration                      *
 *******************************************************************************/

#define SysTick_Load            (TEN_MS)

/*******************************************************************************
 *                            Available Reload Values                          *
 *******************************************************************************/

#define TEN_MS                  (160000)        /* 160,000    clock ticks */
#define HALF_SECOND             (8000000)       /* 800,000    clock ticks */
#define ONE_SECOND              (16000000)      /* 16,000,000 clock ticks */
#define FIVE_SECONDS            (80000000)      /* 80,000,000 clock ticks */

#endif /* __Systick_Cfg_H__ */