/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				3 JAN 2021									*/
/*	Version					: 				V02											*/
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

#include "shift_register.h"

void S2P_voidSend8BitSynchronous(u8 u8Data)
{
	s8 s8Counter=0;
	for(s8Counter=7; s8Counter>=0; s8Counter--)
	{
		//Send bit by bit starting by MSB
		GPIO_voidSetPinValue(S2P_SERIAL_DATA, GET_BIT(u8Data , s8Counter));
		//Send Pulse 
		GPIO_voidSetPinValue(S2P_SHIFT_CLK, HIGH);
		TIM_voidDelay(TIMER3, 8, 1);
		GPIO_voidSetPinValue(S2P_SHIFT_CLK, LOW);
		TIM_voidDelay(TIMER3, 8, 1);
		
	}
	//Send pulse to Storage CLK
	GPIO_voidSetPinValue(S2P_STORAGE_CLK, HIGH);
	TIM_voidDelay(TIMER3, 8, 1);
	GPIO_voidSetPinValue(S2P_STORAGE_CLK, LOW);
	TIM_voidDelay(TIMER3, 8, 1);
}

void S2P_voidSend16BitSynchronous(u16 u16Data)
{
	s8 s8Counter=0;
	for(s8Counter=15; s8Counter>=0; s8Counter--)
	{
		//Send bit by bit starting by MSB
		GPIO_voidSetPinValue(S2P_SERIAL_DATA, GET_BIT(u16Data , s8Counter));
		//Send Pulse
		GPIO_voidSetPinValue(S2P_SHIFT_CLK, HIGH);
		TIM_voidDelay(TIMER3, 8, 1);
		GPIO_voidSetPinValue(S2P_SHIFT_CLK, LOW);
		TIM_voidDelay(TIMER3, 8, 1);
	}
	//Send pulse to Storage CLK
	GPIO_voidSetPinValue(S2P_STORAGE_CLK, HIGH);
	TIM_voidDelay(TIMER3, 8, 1);
	GPIO_voidSetPinValue(S2P_STORAGE_CLK, LOW);
	TIM_voidDelay(TIMER3, 8, 1);
}
