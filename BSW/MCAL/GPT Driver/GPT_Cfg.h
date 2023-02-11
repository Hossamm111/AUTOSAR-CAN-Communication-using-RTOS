/********************************************************************************/
/* Module Name  : GPT_Cfg.h						        */
/* Author       : Hossam				        		*/
/* Purpose      : Configuration file for GPT Driver		                */
/********************************************************************************/

#ifndef __GPT_Cfg_H__
#define __GPT_Cfg_H__

/*******************************************************************************
 *                            GPT Reload Configurations                        *
 *******************************************************************************/

#define Timer0_Load             (ONE_SECOND)
#define Timer1_Load             (FIVE_SECONDS)

/*******************************************************************************
 *                            Available Reload Values                          *
 *******************************************************************************/

#define TEN_MS                  (160000)        /* 160,000    clock ticks */
#define HALF_SECOND             (8000000)       /* 800,000    clock ticks */
#define ONE_SECOND              (16000000)      /* 16,000,000 clock ticks */
#define FIVE_SECONDS            (80000000)      /* 80,000,000 clock ticks */

#endif /* __GPT_Cfg_H__ */