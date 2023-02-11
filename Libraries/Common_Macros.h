/********************************************************************************/
/* Module Name  : Common_Macros.h						*/
/* Author       : Hossam							*/
/* Purpose      : Commonly used Macros		 			        */
/********************************************************************************/

#ifndef __COMMON_MACROS__
#define __COMMON_MACROS__

 /* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

 /* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

 /* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

 /* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG = (REG>>num) | (REG << ((sizeof(REG) * 8)-num)) )

 /* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG = (REG<<num) | (REG >> ((sizeof(REG) * 8)-num)) )

 /* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

 /* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#endif /* __COMMON_MACROS__ */