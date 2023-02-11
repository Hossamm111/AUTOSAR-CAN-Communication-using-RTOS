/********************************************************************************/
/* Module Name  : Led_Cfg.h						        */
/* Author       : Hossam				        		*/
/* Purpose      : Configuration file for LED Module		 		*/
/********************************************************************************/

#ifndef __Led_Cfg_H__
#define __Led_Cfg_H__

/*******************************************************************************
 *                           Enable LED Functionalities                        *
 *******************************************************************************/

#define ENABLE_LED_FUNCTIONALITIES      (1)
#define YES                             (1)
#define NO                              (0)

/*******************************************************************************
 *                           LED Module Configurations                         *
 *******************************************************************************/

  /* Alias for LED pins */
#define RED_LED         PORT_F_PIN_1
#define BLUE_LED        PORT_F_PIN_2
#define GREEN_LED       PORT_F_PIN_3

#endif /* __Led_Cfg_H__ */