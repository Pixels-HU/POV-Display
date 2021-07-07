/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				29 SEP 2020									*/	
/*	Version					: 				V01											*/	
/*																						*/
/*																						*/
/****************************************************************************************/

#include "std_types.h"
#include "bit_maths.h"
#include "stm32f103c8t6_rcc.h"


void RCC_voidInitSysClock(void)
{
	#if (RCC_CLOCK_TYPE ==	RCC_HSE_CRYSTAL)
		RCC_CR 	 = 0x00010000; 		/*	Enable HSE without bypass			*/
		RCC_CFGR = 0x00000001;
		
	#elif   RCC_CLOCK_TYPE ==   RCC_HSE_RC
		RCC_CR 	 = 0x00000000;		/*	Enable HSE with bypass				*/
		RCC_CFGR = 0x00000001;
		
	#elif   RCC_CLOCK_TYPE ==   RCC_HSI
		RCC_CR 	 = 0x00000001;		/*	Enable HSI							*/
		RCC_CFGR = 0x00000000;
	
	#elif   (RCC_CLOCK_TYPE ==   RCC_PLL)
		#if RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
			RCC_CR = 0x01000001; 	/*	Enable HSI & PLL					*/
			switch(RCC_PLL_MUL_VAL)
			{
				case 2: 	RCC_CFGR == 0x00000002;		break;	/* PLL input clock * 2 */

				case 3:		RCC_CFGR == 0x00040002;		break;	/* PLL input clock * 3 */
				
				case 4:		RCC_CFGR == 0x00080002;		break;	/* PLL input clock * 4 */
				
				case 5:		RCC_CFGR == 0x000C0002;		break;	/* PLL input clock * 5 */
				
				case 6:		RCC_CFGR == 0x00100002;		break;	/* PLL input clock * 6 */
				
				case 7:		RCC_CFGR == 0x00140002;		break;	/* PLL input clock * 7 */
				
				case 8:		RCC_CFGR == 0x00180002;		break;	/* PLL input clock * 8 */
				
				case 9:		RCC_CFGR == 0x001C0002;		break;	/* PLL input clock * 9 */
				
				case 10:	RCC_CFGR == 0x00200002;		break;	/* PLL input clock * 10 */
				
				case 11:	RCC_CFGR == 0x00240002;		break;	/* PLL input clock * 11 */

				case 12:	RCC_CFGR == 0x00280002;		break;	/* PLL input clock * 12 */
				
				case 13:	RCC_CFGR == 0x002C0002;		break;	/* PLL input clock * 13 */
				
				case 14:	RCC_CFGR == 0x00300002;		break;	/* PLL input clock * 14 */
				
				case 15:	RCC_CFGR == 0x00340002;		break;	/* PLL input clock * 15 */
		
				case 16:	RCC_CFGR == 0x00380002;		break;	/* PLL input clock * 16 */
			}

			/************************************************************************/
			/************************************************************************/
			/************************************************************************/
			/************************************************************************/
			/************************************************************************/
			/************************************************************************/

		#elif( (RCC_PLL_INPUT == RCC_PLL_IN_HSE_RC) || (RCC_PLL_INPUT == RCC_PLL_IN_HSE_CRYSTAL) )
			#if(RCC_PLL_INPUT == RCC_PLL_IN_HSE_RC)
				RCC_CR = 0x01010000; 	/*	Enable PLL & HSE with bypass		*/
			#elif(RCC_PLL_INPUT == RCC_PLL_IN_HSE_CRYSTAL)
				RCC_CR = 0x01050000; 	/*	Enable PLL & HSE without bypass		*/
			#endif
			switch(RCC_PLL_MUL_VAL)
			{
				case 2: 	RCC_CFGR == 0x00010002;		break;	/* PLL input clock * 2 */

				case 3:		RCC_CFGR == 0x00050002;		break;	/* PLL input clock * 3 */

				case 4:		RCC_CFGR == 0x00090002;		break;	/* PLL input clock * 4 */

				case 5:		RCC_CFGR == 0x000D0002;		break;	/* PLL input clock * 5 */

				case 6:		RCC_CFGR == 0x00110002;		break;	/* PLL input clock * 6 */

				case 7:		RCC_CFGR == 0x00150002;		break;	/* PLL input clock * 7 */

				case 8:		RCC_CFGR == 0x00190002;		break;	/* PLL input clock * 8 */

				case 9:		RCC_CFGR == 0x001D0002;		break;	/* PLL input clock * 9 */

				case 10:	RCC_CFGR == 0x00210002;		break;	/* PLL input clock * 10 */

				case 11:	RCC_CFGR == 0x00250002;		break;	/* PLL input clock * 11 */
				
				case 12:	RCC_CFGR == 0x00290002;		break;	/* PLL input clock * 12 */

				case 13:	RCC_CFGR == 0x002D0002;		break;	/* PLL input clock * 13 */

				case 14:	RCC_CFGR == 0x00310002;		break;	/* PLL input clock * 14 */

				case 15:	RCC_CFGR == 0x00350002;		break;	/* PLL input clock * 15 */

				case 16:	RCC_CFGR == 0x00390002;		break;	/* PLL input clock * 16 */
			}
		
	#elif((RCC_PLL_INPUT == RCC_PLL_IN_HSE_CRYSTAL_DIV_2)||(RCC_PLL_INPUT == RCC_PLL_IN_HSE_RC_DIV_2))
			#if(RCC_PLL_INPUT == RCC_PLL_IN_HSE_RC_DIV_2)
				RCC_CR = 0x01010000; 	/*	Enable PLL & HSE with bypass		*/
			#elif (RCC_PLL_INPUT == RCC_PLL_IN_HSE_CRYSTAL_DIV_2)
				RCC_CR = 0x01050000; 	/*	Enable PLL & HSE without bypass		*/
			#endif
			switch(RCC_PLL_MUL_VAL)
			{
				case 2: 	RCC_CFGR == 0x00030002;		break;	/* PLL input clock * 2 */

				case 3:		RCC_CFGR == 0x00070002;		break;	/* PLL input clock * 3 */

				case 4:		RCC_CFGR == 0x000B0002;		break;	/* PLL input clock * 4 */

				case 5:		RCC_CFGR == 0x000F0002;		break;	/* PLL input clock * 5 */

				case 6:		RCC_CFGR == 0x00130002;		break;	/* PLL input clock * 6 */

				case 7:		RCC_CFGR == 0x00170002;		break;	/* PLL input clock * 7 */

				case 8:		RCC_CFGR == 0x001B0002;		break;	/* PLL input clock * 8 */

				case 9:		RCC_CFGR == 0x001F0002;		break;	/* PLL input clock * 9 */

				case 10:	RCC_CFGR == 0x00230002;		break;	/* PLL input clock * 10 */

				case 11:	RCC_CFGR == 0x00270002;		break;	/* PLL input clock * 11 */

				case 12:	RCC_CFGR == 0x002B0002;		break;	/* PLL input clock * 12 */

				case 13:	RCC_CFGR == 0x002F0002;		break;	/* PLL input clock * 13 */

				case 14:	RCC_CFGR == 0x00330002;		break;	/* PLL input clock * 14 */

				case 15:	RCC_CFGR == 0x00370002;		break;	/* PLL input clock * 15 */

				case 16:	RCC_CFGR == 0x003B0002;		break;	/* PLL input clock * 16 */
			}
				
		#endif
		//RCC_CFGR = 0x00000010;
		
	#else 
		#error("You have chosen wrong clock type")
	#endif
	
}

void RCC_voidEnableClock(u8 Copy_u8BusID,u8 Copy_u8PerID)
{
	if(Copy_u8PerID < 32)
	{
		switch(Copy_u8BusID)
		{
			case RCC_AHB 	:	SET_BIT(RCC_AHBENR, Copy_u8PerID); 	break;
			case RCC_APB1 	:	SET_BIT(RCC_APB1ENR, Copy_u8PerID);	break;
			case RCC_APB2	:	SET_BIT(RCC_APB2ENR, Copy_u8PerID);	break;
		}

	}
	/*
	else
	{

	}
	*/
}

void RCC_voidDisableClock(u8 Copy_u8BusID,u8 Copy_u8PerID)
{
	if(Copy_u8PerID < 32)
	{
		switch(Copy_u8BusID)
		{
			case RCC_AHB 	:	CLR_BIT(RCC_AHBENR, Copy_u8PerID); 	break;
			case RCC_APB1 	:	CLR_BIT(RCC_APB1ENR, Copy_u8PerID);	break;
			case RCC_APB2	:	CLR_BIT(RCC_APB2ENR, Copy_u8PerID);	break;
		}
	/*}
		else
		{

		}
	*/
	}
	/*
	else
	{

	}
	*/
	
	
}


