/**
 * @Author					:			John Atia Nafady
 * @Date					: 			31-5-2021
 * @Version					:			V03
 */

#include "std_types.h"
#include "bit_maths.h"

#include "stm32f103c8t6_afio.h"
#include "stm32f103c8t6_exti.h"

static void (*EXTI_CallBack[5])(void *Ptr);
void *PtrToInput[5] = {NULL, NULL, NULL, NULL, NULL};

void EXTI_voidEnable(EXTI_Line_t EXTI_LINE_x , EXTI_Mode_t EXTI_Mode)
{
	SET_BIT(EXTI->IMR , EXTI_LINE_x);
	switch(EXTI_Mode)
	{
		case EXTI_ON_RISING_EDGE		:		SET_BIT(EXTI -> RTSR , EXTI_LINE_x);	break;
		case EXTI_ON_FALLING_EDGE		:		SET_BIT(EXTI -> FTSR , EXTI_LINE_x);	break;
		case EXTI_ON_CHANGE			:		SET_BIT(EXTI -> RTSR , EXTI_LINE_x);
										SET_BIT(EXTI -> FTSR , EXTI_LINE_x);	break;
	}
}

void EXTI_voidDisable(EXTI_Line_t EXTI_LINE_x)
{
	CLR_BIT(EXTI->IMR , EXTI_LINE_x);
}

void EXTI_voidSwTrigger(EXTI_Line_t EXTI_LINE_x)
{
	SET_BIT(EXTI->IMR , EXTI_LINE_x);
	CLR_BIT(EXTI->PR , EXTI_LINE_x); //Set Pending Flag
	SET_BIT(EXTI->SWIER , EXTI_LINE_x);
}

void EXTI_voidRemapPort(EXTI_Line_t EXTI_LINE_x, EXTI_SelectPORTx_t EXTI_SelectPORTx)
{
	AFIO_voidExtiRemapPort(EXTI_LINE_x, EXTI_SelectPORTx);
}

void EXTI_voidSetCallBack(EXTI_Line_t EXTI_LINE_x , void (*PtrToFunc)(void*Para) , void *PtrToPara)
{
	EXTI_CallBack[EXTI_LINE_x] = PtrToFunc;
	PtrToInput[EXTI_LINE_x] = PtrToPara;
}

void EXTI0_IRQHandler(void)
{
	EXTI_CallBack[0](PtrToInput[0]);
	SET_BIT(EXTI->PR , 0); //Clear Pending Flag
}

void EXTI1_IRQHandler(void)
{
	EXTI_CallBack[1](PtrToInput[1]);
	SET_BIT(EXTI->PR , 1); //Clear Pending Flag
}

void EXTI2_IRQHandler(void)
{
	EXTI_CallBack[2](PtrToInput[2]);
	SET_BIT(EXTI->PR , 2); //Clear Pending Flag
}

void EXTI3_IRQHandler(void)
{
	EXTI_CallBack[3](PtrToInput[3]);
	SET_BIT(EXTI->PR , 3); //Clear Pending Flag
}

void EXTI4_IRQHandler(void)
{
	EXTI_CallBack[4](PtrToInput[4]);
	SET_BIT(EXTI->PR , 4); //Clear Pending Flag
}
