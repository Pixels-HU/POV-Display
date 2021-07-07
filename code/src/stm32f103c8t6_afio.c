/**
 * @ Author 	: 	John Atia Nafady
 * @ Date 		: 	31-5-2021
 * @ Version	:	V04
 *
 */
#include "std_types.h"
#include "bit_maths.h"
#include "stm32f103c8t6_afio.h"

void AFIO_voidConfigDebugPort(DebugPort_t SWD_JTAG)
{
	AFIO->MAPR &=~((1<<25) | (1<<26) | (1<<27) );
	AFIO->MAPR |= (SWD_JTAG<<25);
}


void AFIO_voidExtiRemapPort(AFIO_ExtiLine_t AFIO_ExtiLine_x, AFIO_ExtiRemapPort_t AFIO_ExtiRemapPort)
{
	u8 u8Index = (AFIO_ExtiLine_x/4);
	u8 u8Local = (AFIO_ExtiLine_x % 4);
	AFIO->EXTICR[u8Index] &= ~(0b1111<<(u8Local*4));
	AFIO->EXTICR[u8Index] |= (AFIO_ExtiRemapPort<<(u8Local*4));
	/*
	AFIO->EXTICR[(AFIO_ExtiLine_x/4)] &= ~(0b1111<<((AFIO_ExtiLine_x%4)*4));
	AFIO->EXTICR[(AFIO_ExtiLine_x/4)] &= ~(0b1111<<((AFIO_ExtiLine_x%4)*4));
	*/
}

void AFIO_voidTimerRemapChannel(AFIO_TIMERx_t AFIO_TIMERx, AFIO_TimerRemap_t AFIO_TimerRemap)
{
	CLR_BIT(AFIO->MAPR , (6 + (AFIO_TIMERx*2) ) );
	if(AFIO_TIMERx != AFIO_TIMER4)
	{
		CLR_BIT(AFIO->MAPR , (7 + (AFIO_TIMERx*2) ) );
	}
	AFIO->MAPR |= (AFIO_TimerRemap<<(6 + (AFIO_TIMERx*2) ) );
}


