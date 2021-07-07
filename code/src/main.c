/**
 * @Author					:			John Atia Nafady
 * @Date					: 			20-4-2021
 * @Version					:			V02
 */


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
#include "shift_register.h"

#include "pov_display.h"


//volatile u8 	ArrowFlag			=	0	;
//volatile s8 	ArrowCounter 		= 	0	;
//volatile u16 	CurrentDistanceBetweenTeeth = 135;  // kant 250 or 2500us


volatile u8 	IR_u8Flag   		=  	0 	;
volatile u8 	HallEffect_u8Flag 	=  	0 	;
volatile u16 	POV_u16Counter		=  	3520;
volatile u8		Frequency_u8Flag 	=  	0 	;
volatile u8 	Calc_u8Flag  		=  	0 	;
volatile u8 	Entery_u8Flag 		= 	0	;
volatile u8 	Motor_u8OneCycleDone = 0;
volatile u32	Motor_u32PeriodicTime = 11111.1 	;
volatile u8 	u8ShiftWord			=	64	;
volatile u8 	POV_u8FlagsIndex	= 	0	;
volatile u8 	POV_u8DisplayFlag	= 	0	;
volatile u16	Motor_Frequency		=  	0 	;
volatile u8 	Motor_u8FreqFlag	= 	0	;
volatile u16	Average_u16Freq[10]	=  {0}	;
//u32 *Ptr_Motor_Frequency = &Motor_Frequency;
const 	 f32	Distance			= 125.6637;
#define 		LEARN						5
#define			MAKE						10
#define 		SHARE						15
#define			WE							20
#define			ARE							25
#define			PIXELS						30
#define 		WE_ARE						35
#define			THANKS						40
#define 		TREND						45
#define 		TRUE						1
#define 		FALSE						0
volatile u8 POV_u8Flags[9] = {WE,LEARN,MAKE,SHARE,WE_ARE,PIXELS,THANKS,TREND,0};



void Calc_voidTime(void)
{
	asm("NOP");
}
/**
 * @Description this function calculates the Motor Frequency
 * by reading the the Frequency for 10-times then taking the average
 * to enhance the precision
 *
 * @Motor_Frequency is 9
 */
//void Calc_voidFreq(void)
//{
//	Motor_u8FreqFlag++;
//	Average_u16Freq[Motor_u8FreqFlag-1] = Motor_Frequency;
//	IR_u8Flag = VOL_PLUS_Button;
//	if(Motor_u8FreqFlag == 10)
//	{
//		Motor_Frequency = Average_u16Freq[0];
//		for(u8 count = 1; count <=9; count++)
//		{
//			Motor_Frequency += Average_u16Freq[count];
//		}
//		Motor_Frequency /= 10;
//		HS2P_voidSend16BitSynchronous(Motor_Frequency);
//		IR_u8Flag = 0;
//	}
//}
void HallEffect(void)
{
	if(HallEffect_u8Flag == TRUE)
	{
		asm("NOP");
	}
	else
	{
		if(Motor_u8OneCycleDone == TRUE)
		{
			Motor_u32PeriodicTime =	TIM_u16GetElapsedTime(TIMER4);
			if( (IR_u8Flag != Button_LEFT) && (IR_u8Flag != Button_RIGHT) )
			{
				if( (Motor_u32PeriodicTime > 1000) &&   (Motor_u32PeriodicTime < 60000) )
				{
					CurrentDistanceBetweenTeeth = ( (Motor_u32PeriodicTime * 135)/11111 );
				}
			}

//			if(IR_u8Flag == POWER_Button)
//				HS2P_voidSend16BitSynchronous( (Motor_u32PeriodicTime/1000) );
//				IR_u8Flag = 0;
//				CurrentDistanceBetweenTeeth = ( (Motor_u32PeriodicTime-50000)/24);
			Motor_u8OneCycleDone = FALSE;
		}
		TIM_voidSetSingleInterval(TIMER4, 80, 60000, Calc_voidTime);
		Motor_u8OneCycleDone = TRUE;
		HallEffect_u8Flag = TRUE;
	}

	/**
	 * @Description the interrupt gives us the Frequency for testing only
	 */
//	if(IR_u8Flag == VOL_PLUS_Button)
//	{
//		Entery_u8Flag = TRUE;
//		IR_u8Flag = FALSE;
//	}
//	if(Entery_u8Flag == TRUE)
//	{
//		MSTK_voidSetSingleInterval(1000000 , Calc_voidFreq);
//		Motor_Frequency = 0;
//		Entery_u8Flag = FALSE;
//		HS2P_voidSend16BitSynchronous(0xffff);
//	}
//	if(HallEffect_u8Flag == TRUE)
//	{
//		asm("NOP");
//	}
//	else
//	{
//		Motor_Frequency++;
//		HallEffect_u8Flag = TRUE;
//	}
}

//	if(HallEffect_u8Flag == 1)
//	{
//		asm("NOP");
//	}
//	else
//	{
//		HallEffect_u8Flag = 1;
//		Entery_u8Flag++;
//		Motor_Frequency++;
//
//		if(Motor_u8OneCycleDone == 1)
//		{
//			Motor_u32PeriodicTime = MSTK_u32GetElapsedTime();
//			if(Motor_u32PeriodicTime > 30000)
//			{
//				CurrentDistanceBetweenTeeth = ( (Motor_u32PeriodicTime-50000)/24);
//			}
//			Motor_u8OneCycleDone = 0;
//		}
//	}
//
//
//	if(Entery_u8Flag == 2)
//	{
//		MSTK_voidSetSingleInterval(500000 , Calc_voidTime);
//		Motor_u8OneCycleDone = 1;
//		Entery_u8Flag = 0;
//	}
//
//	HallEffect_u8Flag = 1;


//P+ Button
void Button_P_PLUS_Action(void)
{
	//IR_u8Flag = POWER_Button;
	if(IR_u8Flag == Button_POWER)
	{
		ArrowCounter++;
		if(ArrowCounter >19)
		{
			ArrowCounter = 0;
		}
	}
	//IR_u8Flag = P_PLUS_Button;
}
//P- Button
void Button_P_MINUS_Action(void)
{
	//IR_u8Flag = POWER_Button;
	if(IR_u8Flag == Button_POWER)
	{
		//ArrowCounter--;
		if( ArrowCounter < 0 )
		{
			ArrowCounter = 19;
		}
	}
	//IR_u8Flag = P_MINUS_Button;
}
//Power Button
void Button_POWER_Action(void)
{
	IR_u8Flag = Button_POWER;
	//HS2P_voidSend16BitSynchronous(0x0000);
}
//>|| Button
void Button_OK_Action(void)
{
	IR_u8Flag = Button_OK;
	POV_u8DisplayFlag = POV_u8Flags[POV_u8FlagsIndex];
	POV_u8FlagsIndex++;
	if(POV_u8FlagsIndex == 9)
	{POV_u8FlagsIndex = 0;}
	//HS2P_voidSend16BitSynchronous(0xFFFF);
	//HS2P_voidSend16BitSynchronous( (1<<7) | (1<<6) );
	//Calc_u8Flag = 1;
	//Frequency_u8Flag = 1;
}
//|<< Button
void Button_LEFT_Action(void)
{
	IR_u8Flag = Button_LEFT;
	CurrentDistanceBetweenTeeth+=10;
}
//>>| Button
void Button_RIGHT_Action(void)
{
	IR_u8Flag = Button_RIGHT;
	CurrentDistanceBetweenTeeth-=10;
}
//VOL+ Button
void Button_VOL_PLUS_Action(void)
{
	//IR_u8Flag = Button_VOL_PLUS;
	if(IR_u8Flag == Button_OK)
	{
		u8ShiftWord++;
	}
}
//VOL- Button
void Button_VOL_MINUS_Action(void)
{
	//IR_u8Flag = Button_VOL_MINUS;
	if(IR_u8Flag == Button_OK)
	{
		u8ShiftWord--;
	}
}



void main(void)
{
	/* Initialize Clock */
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2, 2); 	//Enable RCC for GPIOA
	RCC_voidEnableClock(RCC_APB2, 3); 	//Enable RCC for GPIOB
	RCC_voidEnableClock(RCC_APB2, 0); 	//Enable RCC for AFIO
	RCC_voidEnableClock(RCC_APB2, 11);	//Enable RCC for TIMER1
	RCC_voidEnableClock(RCC_APB1 , 0);	//Enable RCC for GPTimer2
	RCC_voidEnableClock(RCC_APB1 , 1);	//Enable RCC for GPTIMER3
	RCC_voidEnableClock(RCC_APB1 , 2);	//Enable RCC for GPTIMER4



	/* Timers Initialization 	*/
	TIM_voidInit(TIMER2, TIM_NoClkDivison, DOWN_COUNTER);
	TIM_voidInit(TIMER3, TIM_NoClkDivison, DOWN_COUNTER);
	TIM_voidInit(TIMER4, TIM_NoClkDivison, DOWN_COUNTER);

	/* GPIO Initialization 		*/
	GPIO_voidSetPinDir(GPIOA , PIN0 , OUT_PUSHPULL_10MHz);
	GPIO_voidSetPinDir(GPIOA , PIN1 , OUT_PUSHPULL_10MHz);
	GPIO_voidSetPinDir(GPIOA , PIN2 , OUT_PUSHPULL_10MHz);

	/* EXTI PINs Initialization */
//	gPIO_voidSetPinDir(GPIOB , PIN0 , IN_FLOATING);
	GPIO_voidSetPinDir(GPIOB , PIN0 , IN_PULLUP_PULLDOWN);
	GPIO_voidSetPinValue(GPIOB , PIN0 , HIGH);

	MNVIC_voidEnableInterrupt(6);	  	//Enable NVIC for EXTI0
	MNVIC_voidEnableInterrupt(25);		//Enable NVIC for Timer1
	MNVIC_voidEnableInterrupt(28);		//Enable NVIC for GPTimer2

	//EXTI1 Set in Group0 and SubGroup0 to change its Priority
	MNVIC_voidSetPriority(7 , 0 , 0 , NVIC_GROUP_SUB_DISTRIBUTION);
	//EXTI0 Set in Group1 and SubGroup1 to change its Priority
	MNVIC_voidSetPriority(6 , 1 , 1 , NVIC_GROUP_SUB_DISTRIBUTION);


	EXTI_voidRemapPort(EXTI_LINE_0, EXTI_PORTB);	//Set EXTI0 on GPIO B0
	EXTI_voidSetCallBack(EXTI_LINE_0, HallEffect, NULL);
	EXTI_voidEnable(EXTI_LINE_0 , EXTI_ON_FALLING_EDGE);


	IR_voidInit();
	IR_voidSetInterruptPin(EXTI_PORTB , EXTI_LINE_1);
	IR_voidSetCallBack(Button_P_PLUS , Button_P_PLUS_Action);
	IR_voidSetCallBack(Button_P_MINUS , Button_P_MINUS_Action);
	IR_voidSetCallBack(Button_POWER , Button_POWER_Action);
	IR_voidSetCallBack(Button_OK , Button_OK_Action);
	IR_voidSetCallBack(Button_LEFT , Button_LEFT_Action);
	IR_voidSetCallBack(Button_RIGHT , Button_RIGHT_Action);
	IR_voidSetCallBack(Button_VOL_PLUS , Button_VOL_PLUS_Action);
	IR_voidSetCallBack(Button_VOL_MINUS , Button_VOL_MINUS_Action);

	S2P_voidSend16BitSynchronous(0x0000);

	MIX[0] = (POV_u16ShortArrow[0] | POV_u16Num6[0]);
	MIX[1] = (POV_u16ShortArrow[1] | POV_u16Num6[1]);
	MIX[2] = (POV_u16ShortArrow[2] | POV_u16Num6[2]);
	MIX[3] = (POV_u16ShortArrow[3] | POV_u16Num6[3]);
	MIX[4] =  POV_u16ShortArrow[4] ;
	while(1)
	{

		if(HallEffect_u8Flag == 1)
		{
			switch(IR_u8Flag)
			{
			case Button_POWER:
			POV_DisplayClock();
				break;
			case Button_RIGHT:
			POV_DisplayClock();
				break;
			case Button_LEFT:
			POV_DisplayClock();
				break;

			case Button_OK:
				switch(POV_u8DisplayFlag)
				{
				case WE	:
					TIM_voidDelay(TIMER3, 8000, 1000);
					POV_DisplayWord(POV_u16WE , 14);
					break;
				case LEARN	:
					TIM_voidDelay(TIMER3, 8000, 1000);
					POV_DisplayWord(POV_u16LEARN , 29);
					break;
				case MAKE	:
					TIM_voidDelay(TIMER3, 8000, 1000);
					POV_DisplayWord(POV_u16MAKE , 25);
					break;
				case SHARE	:
					TIM_voidDelay(TIMER3, 8000, 1000);
					POV_DisplayWord(POV_u16SHARE , 28);
					break;
				case WE_ARE	:
					TIM_voidDelay(TIMER3, 8000, 1000);
					POV_DisplayWord(POV_u16WE , 14);
					TIM_voidDelay(TIMER3, 8000, 1000);
					POV_DisplayWord(POV_u16ARE , 17);
					break;
				case PIXELS	:
					TIM_voidDelay(TIMER3, 8000, 1000);
					POV_DisplayWord(POV_u16PIXELS , 30);
					break;
				case THANKS	:
					TIM_voidDelay(TIMER3, 8000, 1000);
					POV_DisplayWord(POV_u16THANKS , 36);
					break;
				case TREND	:
					TIM_voidDelay(TIMER3, 8000, 1000);
					POV_DisplayWord(POV_u16TREND , 28);
					break;
				case 0	:
						S2P_voidSend16BitSynchronous(0x0000);
						break;
				}
				break;
			}
			HallEffect_u8Flag = 0;
		}
	}
}

