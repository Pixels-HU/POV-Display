/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				3 OCT 2020									*/	
/*	Version					: 				V01											*/	
/*																						*/
/*																						*/
/****************************************************************************************/



#include "std_types.h"
#include "bit_maths.h"
#include "stm32f103c8t6_nvic.h"




void MNVIC_voidEnableInterrupt(u8 Copy_u8PerID)
{
	if(Copy_u8PerID<32)
	{
		NVIC_ISER0 = 1<<Copy_u8PerID ;
	}
	else if(Copy_u8PerID<=59)
	{
		NVIC_ISER1 = 1<<(Copy_u8PerID-32) ;
	}
	/*
	else
	{
		//return error
	}
	*/	
}

void MNVIC_voidDisableInterrupt(u8 Copy_u8PerID)
{
	if(Copy_u8PerID<32)
	{
		NVIC_ICER0 = 1<<Copy_u8PerID ;
	}
	else if(Copy_u8PerID<=59)
	{
		NVIC_ICER0 = 1<<(Copy_u8PerID-32) ;
	}
	/*
	else
	{
		//return error
	}
	*/	
}

void MNVIC_voidSetPendingFlag(u8 Copy_u8PerID)
{
	if(Copy_u8PerID < 32)
	{
		NVIC_ISPR0 = (1<<Copy_u8PerID) ;
	}
	else if(Copy_u8PerID <= 59)
	{
		NVIC_ISPR1 = 1<<(Copy_u8PerID-32) ;
	}
	/*
	else
	{
		//return error
	}
	*/	
}

void MNVIC_voidClearPendingFlag(u8 Copy_u8PerID)
{
	if(Copy_u8PerID<32)
	{
		NVIC_ICPR0 = 1<<Copy_u8PerID ;
	}
	else if(Copy_u8PerID<=59)
	{
		NVIC_ICPR1 = 1<<(Copy_u8PerID-32) ;
	}
	/*
	else
	{
		//return error
	}
	*/	
}

u8 MNVIC_voidGetActiveFlag(u8 Copy_u8PerID)
{
	u8 local_u8Result=0;
	if(Copy_u8PerID<32)
	{
		local_u8Result = GET_BIT(NVIC_IABR0 , Copy_u8PerID);
	}
	else if(Copy_u8PerID<=59)
	{
		local_u8Result = GET_BIT(NVIC_IABR1 , (Copy_u8PerID-32));
	}
	/*
	else
	{
		//return error
	}
	*/	
	return local_u8Result;
}

void MNVIC_voidSetPriority(s8 Copy_s8InterruptID,u8 Copy_u8GroupPriorty,u8 Copy_u8SubPriorty,u32 Copy_u32Group)
{
	SCB_AIRCR = Copy_u32Group;

	u8 local_u8Priority = (Copy_u8SubPriorty | ( Copy_u8GroupPriorty<<((Copy_u32Group - 0x05FA0300)/256) ) );
	/* Core Peripheral 		*/
	
	/* External Peripheral 	*/
	if(Copy_s8InterruptID >=0)
	{
		NVIC_IPR[Copy_s8InterruptID] = (local_u8Priority<<4);
	}
	

}
