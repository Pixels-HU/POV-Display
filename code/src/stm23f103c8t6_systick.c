/**
 * @ Author 	: John Atia Nafady
 * @ Version 	: V02
 * @ Date		: 20-5-2021
 */

#include "std_types.h"
#include "bit_maths.h"
#include "stm23f103c8t6_systick.h"



static void (* STK_CallBack)(void);
static u8 STK_u8TimeIntervalMode ;
/*
MSTK_voidInit(): MCAL SysTick Core Peripheral Initialization function returns and takes void
Select Clock
Enable/Disable SysTick Interrupt
Enable/Disable SysTick
*/
void MSTK_voidInit()
{
	#if 	(STK_CLK_SOURCE == AHB)
		SET_BIT(STK_CTRL , CLKSOURCE);
	#elif 	(STK_CLK_SOURCE == AHB_DIV_8)
		CLR_BIT(STK_CTRL , CLKSOURCE);
	#endif

}

void MSTK_voidSetBusyWait(u32 Copy_u32Ticks)
{
	SET_BIT(STK_CTRL , MODE);
	STK_LOAD = Copy_u32Ticks;
	while( GET_BIT(STK_CTRL , COUNTFLAG) == 0);
}

void MSTK_voidSetSingleInterval(u32 Copy_u32Ticks , void (*Copy_ptr)(void) )
{
	//MSTK_voidStopInterval();
	CLR_BIT(STK_CTRL , MODE); 			//SysTick is disabled
	STK_VAL = 0;
	STK_CallBack=Copy_ptr;
	STK_LOAD = Copy_u32Ticks; 			//Load the value of Ticks in the Load Register
	SET_BIT(STK_CTRL , MODE); 			//Enable Counter
	SET_BIT(STK_CTRL , TICKINT); 		//SysTick exception request is enabled
	STK_u8TimeIntervalMode = STK_SINGLE_INTERVAL;
}

void MSTK_voidSetPeriodicInterval(u32 Copy_u32Ticks , void (*Copy_ptr)(void) )
{
	STK_CallBack = Copy_ptr;
	STK_LOAD = Copy_u32Ticks; 			//Load the value of Ticks in the Load Register
	SET_BIT(STK_CTRL , MODE); 			//Enable Counter
	SET_BIT(STK_CTRL , TICKINT); 		//SysTick exception request is enabled
	STK_u8TimeIntervalMode = STK_PERIODIC_INTERVAL;
}

void MSTK_voidStopInterval(void)
{

	CLR_BIT(STK_CTRL , MODE); 			//SysTick is disabled
	CLR_BIT(STK_CTRL , TICKINT); 		//SysTick Interrupt is disabled

	//writing in val register will make val = 0 , COUUNFLAG = 0
	STK_LOAD = 0;
	STK_VAL = 0;
}

u32 MSTK_u32GetElapsedTime(void)
{
	u32 local_u32Reslut=0;
	local_u32Reslut = STK_LOAD - STK_VAL;
	return local_u32Reslut;
}

u32 MSTK_u32GetRemainingTime(void)
{
	return STK_VAL;
}

void SysTick_Handler(void)
{
	volatile u8 local_u8TemporaryFlag = 0;
	if(STK_u8TimeIntervalMode == STK_SINGLE_INTERVAL)
	{
		CLR_BIT(STK_CTRL , MODE); 					//SysTick is disabled
		CLR_BIT(STK_CTRL , TICKINT); 				//SysTick Interrupt is disabled

		//writing in STK_VAL register any value will make STK_VAL = 0 , COUUNFLAG = 0
		STK_LOAD = 0;
		STK_VAL	 = 0;
	}

	STK_CallBack(); 													//Call Back Function
	local_u8TemporaryFlag = GET_BIT(STK_CTRL , COUNTFLAG); 				//Read Pending Flag
	CLR_BIT(STK_CTRL , COUNTFLAG); 										//Clear Pending Flag
}


void Delay(u32 Copy_u32TimeInMicroSeconds)
{
	SET_BIT(STK_CTRL , MODE);
	STK_LOAD = Copy_u32TimeInMicroSeconds;
	while( GET_BIT(STK_CTRL , COUNTFLAG) == 0);
}

