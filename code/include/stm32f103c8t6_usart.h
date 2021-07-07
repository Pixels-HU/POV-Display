/**
 * @Author					:			John Atia Nafady
 * @Date					: 			20-5-2021
 * @Version					:			V02
 */

#ifndef _USART_H_
#define _USART_H_


/*
 * Select BaudRate to
 */

#define F_CPU 	8000000

/**
 * Registers begin here
 */
typedef struct
{
		volatile u32 SR;
		volatile u32 DR;
		volatile u32 BRR;
		volatile u32 CR1;
		volatile u32 CR2;
		volatile u32 CR3;
		volatile u32 GTPR;
}USART_TypeDef;

#define USART1  		((USART_TypeDef*)0x40013800)
#define USART2  		((USART_TypeDef*)0x40004400)
#define USART3  		((USART_TypeDef*)0x40004800)
/**
 * Registers End here
 */

typedef enum
{
	USART_1,
	USART_2,
	USART_3
}USART_x_t;

typedef enum
{
	Baud_9600	= 9600		,
	Baud_115200 = 115200	,
	Baud_250000 = 250000
}USART_BaudRate_t;

void USART_voidInit(USART_x_t USART_x , u32 BaudRate);
void USART_voidTransmitChar(USART_x_t USART_x, u8 u8Data);
void USART_voidTransmitString(USART_x_t USART_x,u8 u8Data[]);
u8	 USART_u8ReceiveCharWithTimeOut(USART_x_t USART_x);
u8	 USART_u8ReceiveCharWithPolling(USART_x_t USART_x);
u8 	*USART_u8PtrReceiveStringWithPolling(USART_x_t USART_x);
u8 	*USART_u8PtrReceiveStringWithTimeOut(USART_x_t USART_x);
void voidResetArray(u8 *arr);





#endif
