/**
 * @ Author 	: John Atia Nafady
 * @ Version 	: V02
 * @ Date		: 20-5-2021
 */

#ifndef _DMA_H_
#define _DMA_H_


typedef struct
{
	volatile u32 CCR;
	volatile u32 CNDTR;
	volatile u32 CPAR;
	volatile u32 CMAR;

}CHANNEL_t;

typedef struct
{
	volatile u32 ISR;
	volatile u32 IFCR;
	volatile CHANNEL_t CHANNEL[7];
}DMAx_TypeDef;


#define 	DMA1_BASE_ADDRESS					0x40020000
#define 	DMA2_BASE_ADDRESS					0x40020400
#define		DMA_1								(DMAx_TypeDef*)(DMA1_BASE_ADDRESS)
#define		DMA_2								(DMAx_TypeDef*)(DMA2_BASE_ADDRESS)
typedef enum
{
	DMA1 ,
	DMA2
}DMAx_t;

//void DMA_init(DMA_t* DMAx);
void DMA_voidTransfer(DMAx_t DMAx, u32* u32SourceAddress , u32* u32DestinationAddress , u16 u16BlockLength);

#endif
