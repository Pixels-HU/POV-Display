/**
 * @Author					:			John Atia Nafady
 * @Date					: 			20-5-2021
 * @Version					:			V02
 */
#ifndef _EXTI_H_
#define _EXTI_H_

typedef struct{

	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR;

}EXTI_TypeDef;
#define EXTI 	((EXTI_TypeDef*)0x40010400)

/**
 * EXTI_MODE could be
 * RISING_EDGE
 * FALLING_EDGE
 * ON_CHANGE
 */
typedef enum{
	EXTI_ON_RISING_EDGE,
	EXTI_ON_FALLING_EDGE,
	EXTI_ON_CHANGE
}EXTI_Mode_t;

/**
 * EXTI_LINE = 0 : 15
 */
typedef enum{
	 EXTI_LINE_0 = 0,
	 EXTI_LINE_1  	,
	 EXTI_LINE_2  	,
	 EXTI_LINE_3  	,
	 EXTI_LINE_4  	,
	 EXTI_LINE_5  	,
	 EXTI_LINE_6  	,
	 EXTI_LINE_7  	,
	 EXTI_LINE_8  	,
	 EXTI_LINE_9  	,
	 EXTI_LINE_10  	,
	 EXTI_LINE_11  	,
	 EXTI_LINE_12  	,
	 EXTI_LINE_13  	,
	 EXTI_LINE_14  	,
	 EXTI_LINE_15
}EXTI_Line_t;

typedef enum
{
	EXTI_PORTA = 0	,
	EXTI_PORTB		,
	EXTI_PORTC
}EXTI_SelectPORTx_t;

void EXTI_voidEnable(EXTI_Line_t EXTI_LINE_x , EXTI_Mode_t EXTI_Mode);
void EXTI_voidDisable(EXTI_Line_t EXTI_LINE_x);
void EXTI_voidSwTrigger(EXTI_Line_t EXTI_LINE_x);
void EXTI_voidRemapPort(EXTI_Line_t EXTI_LINE_x, EXTI_SelectPORTx_t EXTI_SelectPORTx);
void EXTI_voidSetCallBack(EXTI_Line_t EXTI_LINE_x , void (*PtrToFunc)(void*Para) , void *PtrToPara);


#endif
