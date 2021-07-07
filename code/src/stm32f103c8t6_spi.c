/**
 * @Author					:			John Atia Nafady
 * @Date					: 			20-4-2021
 * @Version					:			V02
 */
#include "std_types.h"
#include "bit_maths.h"
#include "stm32f103c8t6_gpio.h"
#include "stm32f103c8t6_spi.h"

SPIx_TypeDef *SPI[3] = {SPI_1 , SPI_2 , SPI_3};

void SPI_voidInit(SPIx_t SPIx)
{
	//Load Bits of BaudRate from SPI1_config File
	SPI[SPIx]->CR1 = (SPI1_BAUDRATE<<3);

	//SSI Internal slave select
	SET_BIT(SPI[SPIx]->CR1 , 8);
	
	#if(DATA_FRAME_FORMAT == FRAME_FORMAT_8BIT)
		CLR_BIT(SPI[SPIx]->CR1 , 11);
	#elif(DATA_FRAME_FORMAT == FRAME_FORMAT_16BIT)
		SET_BIT(SPI[SPIx]->CR1 , 11);
	#endif
	
	#if(SLAVE_MANAGEMENT == HARWARE_SLAVE_MANAGEMENT)
		CLR_BIT(SPI[SPIx]->CR1 , 9);
	#elif(SLAVE_MANAGEMENT == SOFTWARE_SLAVE_MANAGEMENT)
		SET_BIT(SPI[SPIx]->CR1 , 9);
	#endif
	
	#if(FIRST_BIT_TRANSMITTED == MSB)
		CLR_BIT(SPI[SPIx]->CR1 , 7);
	#elif(FIRST_BIT_TRANSMITTED == LSB)
		SET_BIT(SPI[SPIx]->CR1 , 7);
	#endif
	
	#if(MASTER_SLAVE_SELECT	== MASTER)
		SET_BIT(SPI[SPIx]->CR1 , 2);
	#elif(MASTER_SLAVE_SELECT	== SLAVE)
		CLR_BIT(SPI[SPIx]->CR1 , 2);
	#endif
	
	#if(CLK_POLARITY == ZERO_WHEN_IDLE)
		CLR_BIT(SPI[SPIx]->CR1 , 1);
	#elif(CLK_POLARITY == ONE_WHEN_IDLE)
		SET_BIT(SPI[SPIx]->CR1 , 1);
	#endif
	
	#if(CLK_PHASE == CAPTURE_DATA_1ST_TRANSITION)
		CLR_BIT(SPI[SPIx]->CR1 , 0);
	#elif(CLK_PHASE == CAPTURE_DATA_2ND_TRANSITION)
		SET_BIT(SPI[SPIx]->CR1 , 0);
	#endif
	
	//SPI1 ENABLE
	SET_BIT(SPI[SPIx]->CR1 , 6);

	//SPI1 -> CR1 = 0b0000 0011 0101 1101 = 0x035D ;

}

u8 	 SPI_u8SendReceiveSynch(SPIx_t SPIx, u8 u8DataToTransmit)
{
	//u8 Local_u8ReceivedData = 0;

	//Send Data
	SPI[SPIx]->DR = u8DataToTransmit;
	// Wait Busy Flag
	while( GET_BIT(SPI[SPIx]->SR , 7) == 1 );

	//while( GET_BIT(SPI1 -> SR , 0) );

	//Load the Received Data
	//Local_u8ReceivedData =

	//return the Received Data
	return SPI[SPIx]->DR;;
}
/*
void MSPI1_voidSendReceiveAsynch(u8 Copy_u8DataToTransmit, void (*CallBack)(u8))
{
	
}

void SPI1_IRQHandler()
{
	//CallBack(SPI1->DR);
}
*/
