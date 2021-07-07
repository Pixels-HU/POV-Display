/**
 * @Author					:			John Atia Nafady
 * @Date					: 			20-5-2021
 * @Version					:			V02
 */

#include "std_types.h"
#include "bit_maths.h"
#include "stm32f103c8t6_gpio.h"

GPIOx_TypeDef *GPIO[3] = {GPIO_A , GPIO_B , GPIO_C};

void GPIO_voidSetPinDir(GPIOx_t GPIOx, GPIO_PINx_t GPIO_PINx, GPIO_Mode_t GPIO_Mode)
{
	if(GPIO_PINx<8)
	{
		GPIO[GPIOx]->CRL &= ~((0x0f)<<(GPIO_PINx*4));
		GPIO[GPIOx]->CRL |= ((GPIO_Mode)<<(GPIO_PINx*4));
	}
	else if(GPIO_PINx<16)
	{
		GPIO[GPIOx]->CRH &= ~((0x0f)<<((GPIO_PINx-8)*4));
		GPIO[GPIOx]->CRH |= ((GPIO_Mode)<<((GPIO_PINx)*4));
	}
}

void GPIO_voidSetPinValue(GPIOx_t GPIOx, GPIO_PINx_t GPIO_PINx, GPIO_OutLevel_t GPIO_OutLevel)
{
	if(GPIO_OutLevel == HIGH)
	{
		SET_BIT(GPIO[GPIOx]->ODR, GPIO_PINx);
	}
	else if(GPIO_OutLevel == LOW)
	{
		CLR_BIT(GPIO[GPIOx]->ODR, GPIO_PINx);
	}
		
}

u8   GPIO_u8GetPinValue(GPIOx_t GPIOx, GPIO_PINx_t GPIO_PINx)
{
	return GET_BIT(GPIO[GPIOx]->IDR, GPIO_PINx);
}


