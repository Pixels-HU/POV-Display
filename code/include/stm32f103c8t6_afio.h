/**
 * @ Author 	: 	John Atia Nafady
 * @ Date 		: 	31-5-2021
 * @ Version	:	V04
 *
 */

#ifndef _AFIO_H_
#define _AFIO_H_

#define PA	0
#define PB	1
#define PC	2

typedef struct{

	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICR[4];
	volatile u32 MAPR2;


}AFIO_TypeDef;

typedef enum
{
	EnableSWD_EnableJTAG 				= 0b000 ,
	EnableSWD_EnableJTAG_WithoutNJTRST	= 0b001 ,
	EnableSWD_DisableJTAG   			= 0b010 ,
	DisableSWD_DisableJTAG 				= 0b100
}DebugPort_t;

typedef enum
{
	AFIO_EXTI_PORTA = 0	,
	AFIO_EXTI_PORTB		,
	AFIO_EXTI_PORTC
}AFIO_ExtiRemapPort_t;

typedef enum
{
	 AFIO_EXTI_LINE_0 = 0	,
	 AFIO_EXTI_LINE_1  		,
	 AFIO_EXTI_LINE_2  		,
	 AFIO_EXTI_LINE_3  		,
	 AFIO_EXTI_LINE_4  		,
	 AFIO_EXTI_LINE_5  		,
	 AFIO_EXTI_LINE_6  		,
	 AFIO_EXTI_LINE_7  		,
	 AFIO_EXTI_LINE_8  		,
	 AFIO_EXTI_LINE_9  		,
	 AFIO_EXTI_LINE_10  	,
	 AFIO_EXTI_LINE_11  	,
	 AFIO_EXTI_LINE_12  	,
	 AFIO_EXTI_LINE_13  	,
	 AFIO_EXTI_LINE_14  	,
	 AFIO_EXTI_LINE_15
}AFIO_ExtiLine_t;

typedef enum
{
	AFIO_TIMER1 = 0,
	AFIO_TIMER2,
	AFIO_TIMER3,
	AFIO_TIMER4
}AFIO_TIMERx_t;

typedef enum
{
	/*************************************************************************
	 * 	For Timer1
	 * ***********************************************************************/
	/**
	 * TIM1_NoRemap:
	 * TIM1_ETR		on	PA12
	 * TIM1_CH1		on	PA8
	 * TIM1_CH2     on	PA9
	 * TIM1_CH3     on	PA10
	 * TIM1_CH4		on	PA11
	 * TIM1_BKIN	on	PB12
	 * TIM1_CH1N    on	PB13
	 * TIM1_CH2N    on	PB14
	 * TIM1_CH3N    on	PB15
	 */
	AFIO_TIM1_NoRemap = 0b00,

	/**
	 * TIM1_Remap1:
	 * TIM1_ETR		on	PA12
	 * TIM1_CH1		on	PA8
	 * TIM1_CH2     on	PA9
	 * TIM1_CH3     on	PA10
	 * TIM1_CH4		on	PA11
	 * TIM1_BKIN	on	PA6
	 * TIM1_CH1N    on	PA7
	 * TIM1_CH2N    on	PB0
	 * TIM1_CH3N    on	PB1
	 */
	AFIO_TIM1_Remap1  = 0b01,

	/**
	 * Note: This Remap is not Available for Stm32f103c8t6
	 * TIM1_Remap2:
	 * TIM1_ETR		on	PE7
	 * TIM1_CH1		on	PE9
	 * TIM1_CH2     on	PE11
	 * TIM1_CH3     on	PE13
	 * TIM1_CH4		on	PE14
	 * TIM1_BKIN	on	PE15
	 * TIM1_CH1N    on	PE8
	 * TIM1_CH2N    on	PE10
	 * TIM1_CH3N    on	PE12
	 */
	AFIO_TIM1_Remap2  = 0b11,

	/*************************************************************************
	 * 	For Timer2
	 * ***********************************************************************/
	/**
	 * TIM2_NoRemap:
	 * TIM2_CH1_ETR on 	PA0
	 * TIM2_CH2 	on 	PA1
	 * TIM2_CH3 	on	PA2
	 * TIM2_CH4 	on	PA3
	 */
	AFIO_TIM2_NoRemap = 0b00,

	/**
	 * TIM2_Remap1:
	 * TIM2_CH1_ETR on 	PA15
	 * TIM2_CH2 	on 	PB3
	 * TIM2_CH3 	on	PA2
	 * TIM2_CH4 	on	PA3
	 */
	AFIO_TIM2_Remap1  = 0b01,

	/**
	 * TIM2_Remap2:
	 * TIM2_CH1_ETR on 	PA0
	 * TIM2_CH2 	on 	PA1
	 * TIM2_CH3 	on	PB10
	 * TIM2_CH4 	on	PB11
	 */
	AFIO_TIM2_Remap2  = 0b10,

	/**
	 * TIM2_Remap1:
	 * TIM2_CH1_ETR on 	PA15
	 * TIM2_CH2 	on 	PB3
	 * TIM2_CH3 	on	PB10
	 * TIM2_CH4 	on	PB11
	 */
	AFIO_TIM2_Remap3  = 0b11,

	/*************************************************************************
	 * 	For Timer3
	 * ***********************************************************************/
	/**
	 * TIM3_NoRemap:
	 * TIM2_CH1		on 	PA6
	 * TIM2_CH2 	on 	PA7
	 * TIM2_CH3 	on	PB0
	 * TIM2_CH4 	on	PB1
	 */
	AFIO_TIM3_NoRemap = 0b00,

	/**
	 * TIM3_Remap1:
	 * TIM2_CH1		on 	PA4
	 * TIM2_CH2 	on 	PA5
	 * TIM2_CH3 	on	PB0
	 * TIM2_CH4 	on	PB1
	 */
	AFIO_TIM3_Remap1  = 0b10,

	/**
	 * TIM3_Remap2:
	 * TIM2_CH1		on 	PC6
	 * TIM2_CH2 	on 	PC7
	 * TIM2_CH3 	on	PC8
	 * TIM2_CH4 	on	PC9
	 */
	AFIO_TIM3_Remap2  = 0b11,

	/*************************************************************************
	 * 	For Timer4
	 * ***********************************************************************/
	/**
	 * TIM4_NoRemap:
	 * TIM2_CH1		on 	PB6
	 * TIM2_CH2 	on 	PB7
	 * TIM2_CH3 	on	PB8
	 * TIM2_CH4 	on	PB9
	 */
	AFIO_TIM4_NoRemap = 0b00,
	/**
	 * Note: This Remap is not Available for Stm32f103c8t6
	 * TIM4_Remap1:
	 * TIM2_CH1		on 	PD12
	 * TIM2_CH2 	on 	PD13
	 * TIM2_CH3 	on	PD14
	 * TIM2_CH4 	on	PD15
	 */
	AFIO_TIM4_Remap1  = 0b01

}AFIO_TimerRemap_t;

#define AFIO 	((AFIO_TypeDef*)0x40010000)


/*************************************************************************
 * @ Functions
 * ***********************************************************************/

void AFIO_voidConfigDebugPort(DebugPort_t SWD_JTAG);
void AFIO_voidExtiRemapPort(AFIO_ExtiLine_t AFIO_ExtiLine_x, AFIO_ExtiRemapPort_t AFIO_ExtiRemapPort);
void AFIO_voidTimerRemapChannel(AFIO_TIMERx_t AFIO_TIMERx, AFIO_TimerRemap_t AFIO_TimerRemap);


#endif
