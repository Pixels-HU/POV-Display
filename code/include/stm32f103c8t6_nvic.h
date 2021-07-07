/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				3 OCT 2020									*/	
/*	Version					: 				V01											*/	
/*																						*/
/*																						*/
/****************************************************************************************/

#ifndef _NVIC_H_
#define _NVIC_H_



//#define			NVIC_BASE_ADDRESS					((u32*)0xE000E100)
#define			NVIC_BASE_ADDRESS					0xE000E100
#define 		NVIC_ISER0							*((volatile u32*)(NVIC_BASE_ADDRESS+0x000))
#define			NVIC_ISER1							*((volatile u32*)(NVIC_BASE_ADDRESS+0x004))
#define			NVIC_ISER2							*((volatile u32*)(NVIC_BASE_ADDRESS+0x008))

#define			NVIC_ICER0							*((volatile u32*)(NVIC_BASE_ADDRESS+0x080))
#define			NVIC_ICER1							*((volatile u32*)(NVIC_BASE_ADDRESS+0x084))
#define			NVIC_ICER2							*((volatile u32*)(NVIC_BASE_ADDRESS+0x088))

#define			NVIC_ISPR0							*((volatile u32*)(NVIC_BASE_ADDRESS+0x100))
#define			NVIC_ISPR1							*((volatile u32*)(NVIC_BASE_ADDRESS+0x104))
#define			NVIC_ISPR2							*((volatile u32*)(NVIC_BASE_ADDRESS+0x108))

#define			NVIC_ICPR0							*((volatile u32*)(NVIC_BASE_ADDRESS+0x180))
#define			NVIC_ICPR1							*((volatile u32*)(NVIC_BASE_ADDRESS+0x184))
#define			NVIC_ICPR2							*((volatile u32*)(NVIC_BASE_ADDRESS+0x188))

#define			NVIC_IABR0							*((volatile u32*)(NVIC_BASE_ADDRESS+0x200))
#define			NVIC_IABR1							*((volatile u32*)(NVIC_BASE_ADDRESS+0x204))
#define			NVIC_IABR2							*((volatile u32*)(NVIC_BASE_ADDRESS+0x208))

#define			NVIC_IPR							((volatile u8*)(NVIC_BASE_ADDRESS+0x300))
#define 		SCB_AIRCR							*((volatile u32*)(0xE000ED00+0x0C))

//#define			NVIC_IPR20							*((volatile u32*)(NVIC_BASE_ADDRESS+0x304))

#define			NVIC_STIR							*((volatile u32*)(NVIC_BASE_ADDRESS+0xE00))






void MNVIC_voidEnableInterrupt(u8 Copy_u8PerID);
void MNVIC_voidDisableInterrupt(u8 Copy_u8PerID);
void MNVIC_voidSetPendingFlag(u8 Copy_u8PerID);
void MNVIC_voidClearPendingFlag(u8 Copy_u8PerID);
u8 MNVIC_voidGetActiveFlag(u8 Copy_u8PerID);
void MNVIC_voidSetPriority(s8 Copy_s8InterruptID,u8 Copy_u8GroupPriorty,u8 Copy_u8SubPriorty,u32 Copy_u32Group);



/*********************
 * Priority Options:
 *  NVIC_Group4_SUB0
 *  NVIC_Group3_SUB1
 *  NVIC_Group2_SUB2
 *  NVIC_Group1_SUB3
 *  NVIC_Group0_SUB4
 *********************/

#define NVIC_GROUP_SUB_DISTRIBUTION 		NVIC_GROUP2_SUB2

#define 	NVIC_GROUP4_SUB0			0x05FA0300	// 4 bits for group & 0 bit for sub
#define 	NVIC_GROUP3_SUB1			0x05FA0400	// 3 bits for group & 1 bit for sub
#define 	NVIC_GROUP2_SUB2			0x05FA0500	// 2 bits for group & 2 bit for sub
#define 	NVIC_GROUP1_SUB3			0x05FA0600	// 1 bits for group & 3 bit for sub
#define 	NVIC_GROUP0_SUB4			0x05FA0700	// 0 bits for group & 4 bit for sub


#endif
