/********************************************************************************/
/* Module Name  : APP.h							        */
/* Author       : Hossam						        */
/* Purpose      : Header File for Application Layer				*/
/********************************************************************************/

#ifndef __APP_H__
#define __APP_H__

/*******************************************************************************
 *                              File Includes                                  *
 *******************************************************************************/

#include "APP_Cfg.h"
#include "../../BSW/Service Layer/Operating System/OS.h"

/*******************************************************************************
 *                             General Definitions                             *
 *******************************************************************************/

#define RESET                   (0)
#define MIN                     (1)
#define MAX                     (3)
   
/*******************************************************************************
 *                             State Definitions                               *
 *******************************************************************************/

#define CLOCKWISE               (0)
#define COUNTERCLOCKWISE        (1)
#define BOTH_PRESSED            (2)
#define IDLE                    (3)
#define TEMP                    (4)

/*******************************************************************************
 *                             LED State Definitions                           *
 *******************************************************************************/
   
#define WHITE                   (0)
#define RED                     (1)
#define BLUE                    (2)
#define GREEN                   (3)
#define VIOLET                  (4)
#define YELLOW                  (5)
#define CYAN                    (6)

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

extern void APP_INIT (void);

extern void APP_START (void);

extern void Master_CheckState(void);

extern void Master_SendState(void);

extern void Slave_CheckState(void);

extern void Slave_SwitchState(void);

extern void LED_Mode (uint8);

extern void Send_Command (uint8);

#endif /* __APP_H__ */
