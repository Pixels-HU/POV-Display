/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				19 MAR 2021									*/
/*	Version					: 				V03											*/
/*	File					:				PovDisplay_program.c																			*/
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

#include "pov_display.h"

volatile u16 	CurrentDistanceBetweenTeeth = 135;  // kant 250 or 2500us
volatile u8 	ArrowFlag			=	0	;
volatile s8 	ArrowCounter 		= 	0	;

u16 POV_u16ShortArrow[5]={0x8400,0x8200,0xff00,0x4100,0x4200};
u16 POV_u16LongArrow[5]={0x20,0x10,0xfff8,0x8,0x10};
//		0x8020,0x8010,0xfff8,0x4008,0x4010
//		0x8100,0x8080,0xFFC0,0x4040,0x4080

u16 POV_u16Num1[3]={0x4,0x2,0x3f};
u16 POV_u16Num2[4]={0x32,0x29,0x29,0x26};
u16 POV_u16Num3[7]={0xe,0x1,0x1,0x7,0x1,0x9,0x6};
//		0x6,0x9,0x1,0x7,0x1,0x9,0x6
u16 POV_u16Num6[4]={0x26,0x25,0x25,0x1e};
u16 POV_u16Num9[7]={0xf,0x8,0x8,0xf,0x9,0x9,0xf};
u16 MIX[5]={0};
//	{0x8400,0x8200,0xff00,0x8200,0x8400};
//	{0x8400,0x8200,0xff00,0x4100,0x4200};

u16 POV_u16PIXELS[30]={
		//P
		0x7f, 0x9, 0x9, 0x6, 0x0,
		//I
		0x41, 0x7f, 0x41, 0x0,
		//X
		0x41, 0x22, 0x14, 0x8, 0x14, 0x22, 0x41, 0x0,
		//E
		0x7f, 0x49, 0x49, 0x0,
		//L
		0x7f, 0x40, 0x40, 0x0,
		//S
		0x2e, 0x49, 0x49, 0x32, 0x0
};
u16 POV_u16WE[14]={
		//W
		0x1f, 0x20, 0x1, 0x20, 0x1e, 0x20, 0x1, 0x20, 0x1f, 0x0,
		//E
		0x7f, 0x49, 0x49, 0x0
};
u16 POV_u16ARE[17]={
	//A
	0x7c, 0x12, 0x11, 0x11, 0x12, 0x7c, 0x0,
	//R
	0x7f, 0x9, 0x9, 0x16, 0x60, 0x0,
	//E
	0x7f, 0x49, 0x49, 0x0
};
u16 POV_u16LEARN[29]={
	//L
	0x7f, 0x40, 0x40, 0x0,
	//E
	0x7f, 0x49, 0x49, 0x0,
	//A
	0x7c, 0x12, 0x11, 0x11, 0x12, 0x7c, 0x0,
	//R
	0x7f, 0x9, 0x9, 0x16, 0x60, 0x0,
	//N
	0x7f, 0x4, 0x8, 0x10, 0x20, 0x40, 0x7f, 0x0
};
u16 POV_u16MAKE[25]={
	//M
	0x7f, 0x2, 0x4, 0xc, 0x4, 0x2, 0x7f, 0x0,
	//A
	0x7c, 0x12, 0x11, 0x11, 0x12, 0x7c, 0x0,
	//K
	0x7f, 0x8, 0x24, 0x22, 0x41, 0x0,
	//E
	0x7f, 0x49, 0x49, 0x0
};
u16 POV_u16SHARE[28]={
	//S
	0x2e, 0x49, 0x49, 0x32, 0x0,
	//H
	0x7f, 0x8, 0x8, 0x8, 0x7f, 0x0,
	//A
	0x7c, 0x12, 0x11, 0x11, 0x12, 0x7c, 0x0,
	//R
	0x7f, 0x9, 0x9, 0x16, 0x60, 0x0,
	//E
	0x7f, 0x49, 0x49, 0x0
};

u16 POV_u16THANKS[36]={
	//T
	0x1, 0x7f, 0x1, 0x0,
	//H
	0x7f, 0x8, 0x8, 0x8, 0x7f, 0x0,
	//A
	0x7c, 0x12, 0x11, 0x11, 0x12, 0x7c, 0x0,
	//N
	0x7f, 0x4, 0x8, 0x10, 0x20, 0x40, 0x7f, 0x0,
	//K
	0x7f, 0x8, 0x24, 0x22, 0x41, 0x0,
	//S
	0x2e, 0x49, 0x49, 0x32, 0x0
};

u16 POV_u16TREND[]={
	//T
	0x1, 0x7f, 0x1, 0x0,
	//R
	0x7f, 0x9, 0x9, 0x16, 0x60, 0x0,
	//E
	0x7f, 0x49, 0x49, 0x0,
	//N
	0x7f, 0x4, 0x8, 0x10, 0x20, 0x40, 0x7f, 0x0,
	//D
	0x7f, 0x41, 0x41, 0x22, 0x1c, 0x0
};



void POV_DisplayMinutes(u8 NumOfMinutes , u16 DistanceBetweenthem )
{
	//if(ArrowCounter == )
	S2P_voidSend16BitSynchronous(0x0000 | 1<<15);

	for(u8 i = 0; i < NumOfMinutes; i++)
	{
		//Clk with 100k Freq
		TIM_voidDelay(TIMER3, 80,  DistanceBetweenthem);
		if(ArrowFlag == ArrowCounter)
		{
			S2P_voidSend16BitSynchronous(   POV_u16LongArrow[0] | 1<<15	 		);
			S2P_voidSend16BitSynchronous(   POV_u16LongArrow[1] | 1<<15	 		);
			S2P_voidSend16BitSynchronous(  (POV_u16LongArrow[2] | 0x3)  | 1<<15	);
			S2P_voidSend16BitSynchronous(   POV_u16LongArrow[3] | 1<<15	 		);
			S2P_voidSend16BitSynchronous(   POV_u16LongArrow[4] | 1<<15	 		);
		}
		else{
			S2P_voidSend16BitSynchronous(0x3 | 1<<15);
		}
		ArrowFlag++;
		S2P_voidSend16BitSynchronous(0x0000 | 1<<15);
		TIM_voidDelay(TIMER3, 80,  DistanceBetweenthem);
	}
}
void POV_DisplayClock(void)
{
	/* Display Number 6 and the arrow */
	S2P_voidSend16BitSynchronous(MIX[0] | 1<<15 );
	S2P_voidSend16BitSynchronous(MIX[1] | 1<<15 );
	S2P_voidSend16BitSynchronous(MIX[2] | 1<<15 );
	S2P_voidSend16BitSynchronous(MIX[3] | 1<<15 );
	S2P_voidSend16BitSynchronous(MIX[4] | 1<<15 );
	//POV_DisplayMinutes(14 , 1200 );
	POV_DisplayMinutes(5 , CurrentDistanceBetweenTeeth );

				/* Display Number 9 */
	S2P_voidSend16BitSynchronous(POV_u16Num9[0] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num9[1] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num9[2] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num9[3] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num9[4] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num9[5] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num9[6] | 1<<15 );
	//POV_DisplayMinutes(14 , 1200 );
	POV_DisplayMinutes(5 , CurrentDistanceBetweenTeeth );

			/* Display Number 12 */
	S2P_voidSend16BitSynchronous(POV_u16Num1[0] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num1[1] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num1[2] | 1<<15 );
	S2P_voidSend16BitSynchronous(0x0000 | 1<<15);
	S2P_voidSend16BitSynchronous(POV_u16Num2[0] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num2[1] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num2[2] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num2[3] | 1<<15 );
	//POV_DisplayMinutes(14 , 1200 );
	POV_DisplayMinutes(5 , CurrentDistanceBetweenTeeth );

			/* Display Number 3 */
	S2P_voidSend16BitSynchronous(POV_u16Num3[0] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num3[1] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num3[2] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num3[3] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num3[4] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num3[5] | 1<<15 );
	S2P_voidSend16BitSynchronous(POV_u16Num3[6] | 1<<15 );
	POV_DisplayMinutes(5 , CurrentDistanceBetweenTeeth );
	ArrowFlag = 0;
//	POV_DisplayMinutes(14 , 1200 );
}
void POV_DisplayWord(u16 *Word , u16 SizeOfWord)
{
	for(u8 i = 0; i<SizeOfWord; i++)
	{
		S2P_voidSend16BitSynchronous(Word[i]);
	}
}

