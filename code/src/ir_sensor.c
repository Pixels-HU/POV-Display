/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				11 FEB 2020									*/
/*	Version					: 				V01											*/
/*																						*/
/*																						*/
/****************************************************************************************/

#include "std_types.h"
#include "bit_maths.h"

#include "stm32f103c8t6_rcc.h"
#include "stm32f103c8t6_nvic.h"
#include "stm23f103c8t6_systick.h"
#include "stm32f103c8t6_gpio.h"
#include "stm32f103c8t6_afio.h"
#include "stm32f103c8t6_exti.h"
#include "stm23f103c8t6_dma.h"
#include "stm32f103c8t6_timer.h"
#include "stm32f103c8t6_usart.h"
#include "stm32f103c8t6_spi.h"

#include "ir_sensor.h"


volatile u8  u8StartFlag    =  0 ;
volatile u32 u32Counter[50] = {0};
volatile u8  u8IndexCounter =  0 ;
volatile u8 ButtonToFunction[15]   =  {0} ;

#define RIGHT	100
#define LEFT	200
#ifndef			NULL
#define 		NULL			((void *)0)
#endif
static void (*_IR_CallBack[15])(void) = {NULL};

/**
 *@brief initialization of  IR_PIN as INPUT Floating
 */
void IR_voidInit(void)
{
	GPIO_voidSetPinDir(IR_PIN , IN_FLOATING);
}
/**
 *
 * @param IR_u8ExtiPort External Interrupt PORT, you can select it to PA or PB or PC
 * @param IR_u8ExtiLine External Interrupt Pin, you can Select it from 0 to 4
 */
void IR_voidSetInterruptPin(EXTI_SelectPORTx_t IR_u8ExtiPort , EXTI_Line_t IR_u8ExtiLine )
{
	//Enable NVIC for EXTIx ,Note:the vector table for EXTI0 = 6 , and EXTI1 = 7
	MNVIC_voidEnableInterrupt(IR_u8ExtiLine + 6);
	EXTI_voidRemapPort(IR_u8ExtiLine, IR_u8ExtiPort);
	EXTI_voidSetCallBack(IR_u8ExtiPort , IR_voidGetFrame, NULL);
	EXTI_voidEnable(IR_u8ExtiLine, EXTI_ON_FALLING_EDGE);
}

void voidTakeAction(u32 u32Decision)
{
	/* TV Remote */
	switch(u32Decision)
	{
		//Power Button (Button_POWER)
		case 0xeb14bd02:
			if(ButtonToFunction[Button_POWER] == 1)
			{_IR_CallBack[Button_POWER]();}
			break;
		//>|| Button (Button_OK)
		case 0xb748bd02:
			if(ButtonToFunction[Button_OK] == 1)
			{_IR_CallBack[Button_OK]();}
			break;
		//>>| Button (Button_RIGHT)
		case 0xe31cbd02:
			if(ButtonToFunction[Button_RIGHT] == 1)
			{_IR_CallBack[Button_RIGHT]();}
			break;
		//|<< Button (Button_LEFT)
		case 0xe11ebd02:
			if(ButtonToFunction[Button_LEFT] == 1)
			{_IR_CallBack[Button_LEFT]();}
			break;
		//P+ Button (Button_P_PLUS)
		case 0xed12bd02:
			if(ButtonToFunction[Button_P_PLUS] == 1)
			{_IR_CallBack[Button_P_PLUS]();}
			break;
		//P- Button (Button_P_MINUS)
		case 0xec13bd02:
			if(ButtonToFunction[Button_P_MINUS] == 1)
			{_IR_CallBack[Button_P_MINUS]();}
			break;

		//VOL+ Button (Button_VOL_PLUS)
		case 0xef10bd02:
			if(ButtonToFunction[Button_VOL_PLUS] == 1)
			{_IR_CallBack[Button_VOL_PLUS]();}
			break;
		//VOL- Button (Button_VOL_MINUS)
		case 0xee11bd02:
			if(ButtonToFunction[Button_VOL_MINUS] == 1)
			{_IR_CallBack[Button_VOL_MINUS]();}
			break;
	}

}
void _voidResetArrayElements(volatile u32 *arr , u8 size)
{
	for(u8 i = 0; i<size; i++)
	{
		arr[i] = 0;
	}
}

void IR_voidReadFrame(void)
{
	u32 u32DataFrame = 0;
	if( (u32Counter[0] >= 10000) && (u32Counter[0] <= 17000) )
	{
		for(u8 i = 1; i<=32; i++)
		{
			if( (u32Counter[i] >= 2000) && (u32Counter[i] <= 2475) )
			{
				SET_BIT(u32DataFrame , (i-1));
			}
			else
			{
				CLR_BIT(u32DataFrame , (i-1));
			}
		}
		voidTakeAction(u32DataFrame);
	}
	u8StartFlag    = 0;
	u8IndexCounter = 0;
	_voidResetArrayElements(u32Counter , 50);
}
void IR_voidGetFrame(void)
{
	if(u8StartFlag == 0)
	{
		//Achieve Time Interval = 200ms = 20000 * 10us
		TIM_voidSetSingleInterval(TIMER2, 80, 20000,  IR_voidReadFrame);
		u8StartFlag = 1;
	}
	else
	{
		u32Counter[u8IndexCounter] = TIM_u16GetElapsedTime(TIMER2);
		//Achieve Time Interval = 200ms = 20000 * 10us
		TIM_voidSetSingleInterval(TIMER2, 80, 20000,  IR_voidReadFrame);
		u8IndexCounter++;
	}
}

void IR_voidSetCallBack(RemoteButton_t RemoteButton , void(*IR_PtrToFunc)(void) )
{
	_IR_CallBack[RemoteButton] = IR_PtrToFunc;
	//Check if the user set the CallBack to the Button
	//if yes, it will Execute the Required CallBack Function
	//if No, it will Execute the NULL CallBack, So this will be a Bug
	ButtonToFunction[RemoteButton] = 1;
}
