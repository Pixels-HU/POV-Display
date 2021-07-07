/**
 * @Author					:			John Atia Nafady
 * @Date					: 			20-5-2021
 * @Version					:			V02
 */

#include "std_types.h"
#include "bit_maths.h"
#include "stm32f103c8t6_usart.h"

USART_TypeDef* USART[3] = {USART1 , USART2 , USART3};

void USART_voidInit(USART_x_t USART_x , u32 BaudRate)
{
	u64 Mantissa = F_CPU/(16*BaudRate);
	f32 Fraction = ( ( F_CPU/(16.0*BaudRate) ) - Mantissa) * 16;
	u8 Fraction_IntegerPart;

	if( Fraction  > 15.0)
	{
		Mantissa++;
		Fraction = 0;
		Fraction_IntegerPart= Fraction;
	}
	else{
		Fraction_IntegerPart = Fraction;
		if( ( (Fraction-Fraction_IntegerPart) * 10) >= 5 )
		{
			Fraction_IntegerPart++;
		}
	}
	//Set BaudRate of USART1
	USART[USART_x]->BRR = (Mantissa << 4 ) | (Fraction_IntegerPart);

	//for 9600 BAUDRATE -> BRR = 0x341
	//USART1->BRR = 0x341;
	//for 115200 BAUDRATE -> BRR = 0x045
	//USART1->BRR = 0x045;
	//for 250000 BAUDRATE -> BRR = 0x020
	//USART1->BRR = 0x020;
	//Receiver enable
	SET_BIT(USART[USART_x]->CR1 , 2);
	//Transmitter  enable
	SET_BIT(USART[USART_x]->CR1 , 3);
	//USART enable
	SET_BIT(USART[USART_x]->CR1 , 13);
	//Clear Status Register
	USART[USART_x]->SR = 0;
}

void USART_voidTransmitChar(USART_x_t USART_x, u8 u8Data)
{
		USART[USART_x]->DR = u8Data;
		//Wait till Transmission complete
		while(GET_BIT(USART[USART_x]->SR , 6) == 0);
		//Clear TC Flag Bit
		CLR_BIT(USART[USART_x]->SR , 6);
}

void USART_voidTransmitString(USART_x_t USART_x,u8 u8Data[])
{
	u8 i=0;
	while(u8Data[i] != '\0')
	{
		USART_voidTransmitChar(USART_x , u8Data[i]);
		i++;
	}
}

u8	 USART_u8ReceiveCharWithTimeOut(USART_x_t USART_x)
{
	u32 timeout = 0;
	u8 Local_u8ReceivedData = 0;
	//Wait till Receive Data From USART
	while(GET_BIT(USART[USART_x]->SR , 5) == 0)
	{
		timeout++;
		if(timeout == 1000000)
		{
			Local_u8ReceivedData = 255;
			break;
		}
	}
	if(Local_u8ReceivedData == 0)
	{
		//Read Data Register
		Local_u8ReceivedData = USART1->DR;
	}
	//Clear RXNE Flag Bit
	CLR_BIT(USART[USART_x]->SR , 5);
	//Return Received Data
	return Local_u8ReceivedData;
}

u8	 USART_u8ReceiveCharWithPolling(USART_x_t USART_x)
{
	//Wait till Receive Data From USART
	while(GET_BIT(USART[USART_x]->SR , 5) == 0);
	//Clear RXNE Flag Bit
	CLR_BIT(USART[USART_x]->SR , 5);
	//Return Data Register
	return (USART[USART_x]->DR);
}




u8 	*USART_u8PtrReceiveStringWithPolling(USART_x_t USART_x)
{
	u8 i=0;
	static u8 Local_u8String[100];

	//Reset Data in the Array
	voidResetArray(Local_u8String);

	while(1)
	{
		Local_u8String[i] = USART_u8ReceiveCharWithPolling(USART_x);
		if(Local_u8String[i] == '\n')		{i++;	break;}
		i++;
	}
	Local_u8String[i] = '\0';
	return Local_u8String;
}

u8 	*USART_u8PtrReceiveStringWithTimeOut(USART_x_t USART_x)
{
	u8 i=0;
	static u8 Local_u8String[100];

	//Reset Data in the Array
	voidResetArray(Local_u8String);

	while(1)
	{
		Local_u8String[i] = USART_u8ReceiveCharWithTimeOut(USART_x);
		if(Local_u8String[i] == '\n')		{i++;	break;}
		i++;
	}
	Local_u8String[i] = '\0';
	return Local_u8String;
}

void voidResetArray(u8 *arr)
{
	u8 i=0;
	while(arr[i] != '\0')
	{
		arr[i]='\0';
		i++;
	}
}
