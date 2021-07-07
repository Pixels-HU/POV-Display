/**
 * @ Author 	: John Atia Nafady
 * @ Version 	: V02
 * @ Date		: 20-5-2021
 */

#include "std_types.h"
#include "bit_maths.h"
#include "stm23f103c8t6_dma.h"


/*
	1-memory to memory
	2-very high
	3-source size , destination size = 32-bit
	4-Memory Increment (MINC) , Peripheral Increment (PINC) activated
	5-no circular
	6-direction
	7-transfer interrupt enable
*/

DMAx_TypeDef *DMA[2] = {DMA_1 , DMA_2};

void DMA_voidTransfer(DMAx_t DMAx , u32* u32SourceAddress , u32* u32DestinationAddress , u16 u16BlockLength)
{
	DMA[DMAx]->CHANNEL[0].CCR = 0;
	DMA[DMAx]->CHANNEL[0].CNDTR = u16BlockLength;
	//set the source may be Peripheral or Memory
	DMA[DMAx]->CHANNEL[0].CPAR = u32SourceAddress;
	//set the source may be Memory or Peripheral
	DMA[DMAx]->CHANNEL[0].CMAR = u32DestinationAddress;
	DMA[DMAx]->CHANNEL[0].CCR = (1<<14) | (1<<11) | (1<<9) |(1<<6) | (1<<1) | (1<<0) ;

	//what is circular mode?
}


void DMA1_Channel1_IRQHandler(void)
{

}
