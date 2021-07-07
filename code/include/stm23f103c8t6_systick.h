/**
 * @ Author 	: John Atia Nafady
 * @ Version 	: V02
 * @ Date		: 20-5-2021
 */

#ifndef _SYSTICK_H_
#define _SYSTICK_H_
/*
you Can select Clock Source of SysTick to: AHB or AHB_DIV_2
*/
#define	STK_CLK_SOURCE			AHB_DIV_8

/**
 * Registers begin here
 */

// Registers
#define 		STK_BASE_ADDRESS			0xE000E010
#define			STK_CTRL					*((volatile u32*)(STK_BASE_ADDRESS+0x00))
#define			STK_LOAD					*((volatile u32*)(STK_BASE_ADDRESS+0x04))
#define			STK_VAL						*((volatile u32*)(STK_BASE_ADDRESS+0x08))
#define			STK_CALIB					*((volatile u32*)(STK_BASE_ADDRESS+0x0C))

//BITS of STK_CTRL Register
#define			COUNTFLAG					16
#define			CLKSOURCE					2
#define			TICKINT						1
#define			MODE						0


#define 		AHB							0
#define 		AHB_DIV_8					1


#define 		STK_SINGLE_INTERVAL			0
#define 		STK_PERIODIC_INTERVAL		1


/**
 * Registers end here
 */

/*
MSTK_voidInit(): MCAL SysTick Core Peripheral Initialization function returns and takes void
Select Clock
Enable/Disable SysTick Interrupt
Enable/Disable SysTick
*/
void MSTK_voidInit(void);

void MSTK_voidSetBusyWait(u32 Copy_u32Ticks);

void Delay(u32 Copy_u32TimeInMicroSeconds);

void MSTK_voidSetSingleInterval(u32 Copy_u32Ticks , void (*Copy_ptr)(void) );

void MSTK_voidSetPeriodicInterval(u32 Copy_u32Ticks , void (*Copy_ptr)(void) );

void MSTK_voidStopInterval(void);

u32 MSTK_u32GetElapsedTime(void);

u32 MSTK_u32GetRemainingTime(void);


#endif
