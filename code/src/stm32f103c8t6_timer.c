/**
 * @ Author 	: 	John Atia Nafady
 * @ Date 		: 	31-5-2021
 * @ Version	:	V04
 *
 */


#include "std_types.h"
#include "bit_maths.h"
#include "stm32f103c8t6_afio.h"
#include "stm32f103c8t6_timer.h"



volatile u8 u8TimeIntervalMode[4];
void(*TIMx_CallBack[4])(void);
TIMx_TypeDef* TIMER[4] = { TIM1 , TIM2 , TIM3 , TIM4 };


void TIM_voidInit(TIMERx_t TIMERx , TIM_SysClkDivison_t TIM_SysClkDivison , COUNTER_Mode_t COUNTER_Mode)
{
	//Reset Registers
	TIMER[TIMERx]->CR1  = 0;
	TIMER[TIMERx]->DIER = 0;
	TIMER[TIMERx]->SR   = 0;
	TIMER[TIMERx]->SMCR = 0;

	/**
	 * @ Set System Clock Division to TIMERx
	 * @ Case No Clock Division 	-> Clear Bit8 and Bit9 in CR1 Register
	 * @ Case Clock Division By 2 	-> Set Bit8 and Clear Bit9 in CR1 Register
	 * @ Case Clock Division By 4 	-> Clear Bit8 and Set Bit9 in CR1 Register
	 */
	TIMER[TIMERx]->CR1 = (TIM_SysClkDivison<<8);
	//PUT_BITS(TIMER[TIMERx]->CR1 , 0b11<<8 , TIM_SysClkDivison<<8);

	if(COUNTER_Mode == UP_COUNTER)
	{
		//Reset Bit4 DIR to use Counter as up counter
		CLR_BIT(TIMER[TIMERx]-> CR1 , 4);
	}
	else if (COUNTER_Mode == DOWN_COUNTER)
	{
		//Set Bit4 DIR to use Counter as down counter
		SET_BIT(TIMER[TIMERx]-> CR1 , 4);
	}
	//Set Bit7 ARPE to activate Auto-reload preload enable, TIMER[TIMERx]_ARR register is buffered
	SET_BIT(TIMER[TIMERx]-> CR1 , 7);
	//Set Bit2 URS to generate an update interrupt or DMA request Only  at counter overflow/underflow Mode
	SET_BIT(TIMER[TIMERx]-> CR1 , 2);
	//CLR Bit0 UIE to disable Update interrupt
	CLR_BIT(TIMER[TIMERx]->DIER , 0);
}

void TIM_voidDelay(TIMERx_t TIMERx  , u16 TIM_u16Prescaler , u16 TIM_u16Ticks )
{
	//CK_CNT = fCK_PSC/(TIM1->PSC+1)
	//Counter Clk = ClkFreq/(Prescaler+1)
	//Set Prescaler
	TIMER[TIMERx]->PSC = ( TIM_u16Prescaler - 1 );
	//Auto reload value
	TIMER[TIMERx]->ARR = TIM_u16Ticks;
	//Set Bit0 UG to update Counter & Prescaler
	SET_BIT(TIMER[TIMERx]->EGR , 0);
	//Set Bit0 CEN to enable counter
	SET_BIT(TIMER[TIMERx]-> CR1, 0);
	//wait till interrupt flag
	while( GET_BIT(TIMER[TIMERx]->SR , 0) == 0 );
	//CLR Bit0 CEN to disable counter
	CLR_BIT(TIMER[TIMERx]-> CR1, 0);
	//Clear Interrupt Flag
	CLR_BIT(TIMER[TIMERx]->SR , 0) ;
}

void TIM_voidSetSingleInterval(TIMERx_t TIMERx, u16 TIM_u16Prescaler ,  u16 TIM_u16Ticks , void(*PtrToFunc)(void) )
{
	u8TimeIntervalMode[TIMERx] = SINGLE_INTERVAL;
	//Save Callback Function
	TIMx_CallBack[TIMERx] = PtrToFunc;

	//CK_CNT = fCK_PSC/(TIM1->PSC+1)
	//Counter Clk = ClkFreq/(Prescaler+1)
	//Set Prescaler
	TIMER[TIMERx]->PSC = ( TIM_u16Prescaler - 1 );
	//Auto reload value
	TIMER[TIMERx]->ARR = TIM_u16Ticks;
	//Set Bit0 UG to update Counter & Prescaler
	SET_BIT(TIMER[TIMERx]->EGR , 0);
	//Set Bit0 UIE to Enable Update interrupt
	SET_BIT(TIMER[TIMERx]->DIER , 0);
	//Set Bit0 CEN to enable counter
	SET_BIT(TIMER[TIMERx]-> CR1, 0);
}
void TIM_voidSetPeriodicInterval(TIMERx_t TIMERx ,  u16 TIM_u16Prescaler , u16 TIM_u16Ticks , void(*PtrToFunc)(void) )
{
	u8TimeIntervalMode[TIMERx] = PERIODIC_INTERVAL;
	//Save Callback Function
	TIMx_CallBack[TIMERx] = PtrToFunc;
	//Counter Clk = ClkFreq/(Prescaler+1)
	TIMER[TIMERx]->PSC = ( TIM_u16Prescaler - 1 );
	//Auto reload value
	TIMER[TIMERx]->ARR = TIM_u16Ticks;
	//Set Bit0 UG to update Counter & Prescaler
	SET_BIT(TIMER[TIMERx]->EGR , 0);
	//Set Bit0 CEN to enable counter
	SET_BIT(TIMER[TIMERx]-> CR1, 0);
	//Set Bit0 UIE to Enable Update interrupt
	SET_BIT(TIMER[TIMERx]->DIER , 0);
}

u16  TIM_u16GetElapsedTime(TIMERx_t TIMERx)
{
	u16 local_u16Reslut=0;
	local_u16Reslut = ( (TIMER[TIMERx]->ARR) - (TIMER[TIMERx]->CNT) );
	return local_u16Reslut;
}
u16  TIM_u16GetRemainingTime(TIMERx_t TIMERx)
{
	return TIMER[TIMERx]->CNT;
}

void TIM_voidRemapChannel(TIMERx_t TIMERx,TIM_REMAP_t TIM_REMAP)
{
	AFIO_voidTimerRemapChannel(TIMERx , TIM_REMAP);
}

void TIM_voidConfigurePWM(TIMERx_t TIMERx, TIM_Channel_t TIM_Channel_x , TIM_ChannelPolarity_t TIM_ChannelPolarity , PWM_Mode_t PWM_Mode_x)
{
	switch(TIM_Channel_x)
	{
	case TIM_CHANNEL_1 :
		if(PWM_Mode_x == PWM_MODE_1)
		//Bit(OC1M) Output compare 1 Preload enable to Select PWM Mode 1 for Channel 1
		{
			TIMER[TIMERx]->CCMR1 &=~(1<<4);
			TIMER[TIMERx]->CCMR1 |= (1<<5) | (1<<6) ;
		}
		else if(PWM_Mode_x == PWM_MODE_2)
		{
			TIMER[TIMERx]->CCMR1 |= (1<<4) | (1<<5) | (1<<6) ;
		}
		//Set Bit (OC1PE) for Channel 1
		SET_BIT(TIMER[TIMERx]->CCMR1 , 3);
		if(TIM_ChannelPolarity == ActiveHigh)
		{
			//Bit1 CC1P: Capture/Compare 1 output polarity , Polarity of Channel 1 is active High
			CLR_BIT(TIMER[TIMERx]->CCER , 1);
		}

		else if(TIM_ChannelPolarity == ActiveLow)
		{
			//Bit1 CC1P: Capture/Compare 1 output polarity ,Polarity of Channel 1 is active Low
			SET_BIT(TIMER[TIMERx]->CCER , 1);
		}
		//activate Channel 1 Bit0 CC1E: Capture/Compare 1 output enable
		SET_BIT(TIMER[TIMERx]->CCER , 0);
		break;

					/***************************************************/

	case TIM_CHANNEL_2 :
		if(PWM_Mode_x == PWM_MODE_1)
		{
		//Bit(OC2M) Output compare 2 Preload enable to Select PWM Mode 1 for Channel 2
			TIMER[TIMERx]->CCMR1 &=~(1<<12); 		TIMER[TIMERx]->CCMR1 |= (1<<13) | (1<<14) ;
		}
		else if(PWM_Mode_x == PWM_MODE_2)
		{
			TIMER[TIMERx]->CCMR1 |= (1<<12) | (1<<13) | (1<<14) ;
		}
		//Set Bit (OC2PE) for Channel 2
		SET_BIT(TIMER[TIMERx]->CCMR1 , 11);
		if(TIM_ChannelPolarity == ActiveHigh)
		{
			//Bit5 CC2P: Capture/Compare 2 output polarity , Polarity of Channel 2 is active High
			CLR_BIT(TIMER[TIMERx]->CCER , 5);
		}

		else if(TIM_ChannelPolarity == ActiveLow)
		{
			//Bit5 CC2P: Capture/Compare 2 output polarity , Polarity of Channel 2 is active Low
			SET_BIT(TIMER[TIMERx]->CCER , 5);
		}
		//activate Channel 2 Bit4 CC2E: Capture/Compare 2 output enable
		SET_BIT(TIMER[TIMERx]->CCER , 4);
		break;
						/***************************************************/
	case TIM_CHANNEL_3 :
		if(PWM_Mode_x == PWM_MODE_1)
		{
			//Bit(OC3M) Output compare 3 Preload enable to Select PWM Mode 1 for Channel 3
			TIMER[TIMERx]->CCMR2 &=~(1<<4); 		TIMER[TIMERx]->CCMR2 |= (1<<5) | (1<<6) ;
		}
		else if(PWM_Mode_x == PWM_MODE_2)
		{
			TIMER[TIMERx]->CCMR2 |= (1<<4) | (1<<5) | (1<<6) ;
		}
		//Set Bit (OC3PE) for Channel 3
		SET_BIT(TIMER[TIMERx]->CCMR2 , 3);
		if(TIM_ChannelPolarity == ActiveHigh)
		{
			//Bit9 CC3P: Capture/Compare 3 output polarity , Polarity of Channel 3 is active High
			CLR_BIT(TIMER[TIMERx]->CCER , 9);
		}
		else if(TIM_ChannelPolarity == ActiveLow)
		{
			//Bit9 CC3P: Capture/Compare 3 output polarity , Polarity of Channel 3 is active Low
			SET_BIT(TIMER[TIMERx]->CCER , 9);
		}
		//activate Channel 3 Bit8 CC3E: Capture/Compare 3 output enable
		SET_BIT(TIMER[TIMERx]->CCER , 8);
		break;
					/***************************************************/
	case TIM_CHANNEL_4 :
		if(PWM_Mode_x == PWM_MODE_1)
		{
			//Bit(OC4M) Output compare 4 Preload enable to Select PWM Mode 1 for Channel 4
			TIMER[TIMERx]->CCMR2 &=~(1<<12); 		TIMER[TIMERx]->CCMR2 |= (1<<13) | (1<<14) ;
		}

		else if(PWM_Mode_x == PWM_MODE_2)
		{
			TIMER[TIMERx]->CCMR2 |= (1<<12) | (1<<13) | (1<<14) ;
		}
		//Set Bit (OC4PE) for Channel 4
		SET_BIT(TIMER[TIMERx]->CCMR2 , 11);
		if(TIM_ChannelPolarity == ActiveHigh)
		{
			//Bit13 CC4P: Capture/Compare 3 output polarity ,Polarity of Channel 4 is active High
			CLR_BIT(TIMER[TIMERx]->CCER , 13);
		}

		else if(TIM_ChannelPolarity == ActiveLow)
		{
			//Bit13 CC4P: Capture/Compare 3 output polarity , Polarity of Channel 4 is active Low
			SET_BIT(TIMER[TIMERx]->CCER , 13);
		}
		//activate Channel 4 Bit12 CC4E: Capture/Compare 4 output enable
		SET_BIT(TIMER[TIMERx]->CCER , 12);
		break;
	}
}

void TIM_voidSetDutyCycle(TIMERx_t TIMERx, TIM_Channel_t TIM_Channel_x , u16 TIM_u16DutyCycle )
{
	//Set Duty Cycle for Channelx for TIMERx
	TIMER[TIMERx]->CCR[TIM_Channel_x] = TIM_u16DutyCycle;
}
void TIM_voidStartPWM(TIMERx_t TIMERx, u16 TIM_u16Prescaler , u16 TIM_u16Period)
{
	//Set Prescaler
	TIMER[TIMERx]->PSC = ( TIM_u16Prescaler - 1 );
	//Auto reload value
	TIMER[TIMERx]->ARR = TIM_u16Period-1;
	//BIT (ARPE)  Auto-reload preload enable
	SET_BIT(TIMER[TIMERx]->CR1 , 7);
	//Set Bit0 UG to update Counter & Prescaler
	SET_BIT(TIMER[TIMERx]->EGR , 0);
	//Set Bit0 CEN to enable counter
	SET_BIT(TIMER[TIMERx]-> CR1, 0);
}






/******************************************************
 * @ IRQ
 ******************************************************/

void TIM1_UP_IRQHandler(void)
{
	if(u8TimeIntervalMode[TIMER1]== SINGLE_INTERVAL)
	{
		//CLR Bit0 UIE to Disable Update interrupt
		CLR_BIT(TIMER[TIMER1]->DIER , 0);
		//CLR Bit0 CEN to disable counter
		CLR_BIT(TIMER[TIMER1]-> CR1, 0);
	}
	TIMx_CallBack[TIMER1]();
	//Clear UnderFlow Interrupt Flag
	CLR_BIT(TIMER[TIMER1]->SR , 0) ;
}

void TIM2_IRQHandler(void)
{
	if(u8TimeIntervalMode[TIMER2] == SINGLE_INTERVAL)
	{
		//CLR Bit0 UIE to Disable Update interrupt
		CLR_BIT(TIMER[TIMER2]->DIER , 0);
		//CLR Bit0 CEN to disable counter
		CLR_BIT(TIMER[TIMER2]-> CR1, 0);
	}
	TIMx_CallBack[TIMER2]();
	//Clear UnderFlow Interrupt Flag
	CLR_BIT(TIM2->SR , 0) ;
}

void TIM3_IRQHandler(void)
{
	if(u8TimeIntervalMode[TIMER3] == SINGLE_INTERVAL)
	{
		//CLR Bit0 UIE to Disable Update interrupt
		CLR_BIT(TIMER[TIMER3]->DIER , 0);
		//CLR Bit0 CEN to disable counter
		CLR_BIT(TIMER[TIMER3]-> CR1, 0);
	}
	TIMx_CallBack[TIMER3]();
	//Clear UnderFlow Interrupt Flag
	CLR_BIT(TIMER[TIMER3]->SR , 0) ;
}

void TIM4_IRQHandler(void)
{
	if(u8TimeIntervalMode[TIMER4] == SINGLE_INTERVAL)
	{
		//CLR Bit0 UIE to Disable Update interrupt
		CLR_BIT(TIMER[TIMER4]->DIER , 0);
		//CLR Bit0 CEN to disable counter
		CLR_BIT(TIMER[TIMER4]-> CR1, 0);
	}
	TIMx_CallBack[TIMER4]();
	//Clear UnderFlow Interrupt Flag
	CLR_BIT(TIMER[TIMER4]->SR , 0) ;
}


