/********************************************************************************/
/* Module Name  : Button_Cfg.h						        */
/* Author       : Hossam				        		*/
/* Purpose      : Configuration file for Button Module		 		*/
/********************************************************************************/

#ifndef __Button_Cfg_H__
#define __Button_Cfg_H__

/*******************************************************************************
 *                         Enable Button Functionalities                       *
 *******************************************************************************/

#define ENABLE_BUTTON_FUNCTIONALITIES   (1)
#define YES                             (1)
#define NO                              (0)

/*******************************************************************************
 *                         Button Module Configurations                        *
 *******************************************************************************/

  /* Alias for Switch pins */
#define Button1         PORT_F_PIN_0
#define Button2         PORT_F_PIN_4

#endif /* __Button_Cfg_H__ */