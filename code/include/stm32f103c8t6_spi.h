/**
 * @Author					:			John Atia Nafady
 * @Date					: 			20-4-2021
 * @Version					:			V02
 */
#ifndef _SPI_H_
#define _SPI_H_


#define SPI1_SlavePIN  GPIOA,0
/*
 assign SPI1_SlavePIN in pairs such as GPIOx,PINx
 */

/*****************************************************************/

#define DATA_FRAME_FORMAT		FRAME_FORMAT_8BIT
/*
you can select DATA_FRAME_FORMAT between 2 options:
FRAME_FORMAT_8BIT
FRAME_FORMAT_16BIT
*/

/*****************************************************************/

#define SLAVE_MANAGEMENT		SOFTWARE_SLAVE_MANAGEMENT
/*
you can select SLAVE_MANAGEMENT between 2 options:
SOFTWARE_SLAVE_MANAGEMENT
HARWARE_SLAVE_MANAGEMENT
*/

/*****************************************************************/

#define FIRST_BIT_TRANSMITTED		MSB
/*
you can select FIRST_BIT_TRANSMITTED between 2 options:
MSB
LSB
*/

/*****************************************************************/

#define MASTER_SLAVE_SELECT			MASTER
/*
you can select MASTER_SLAVE_SELECT from this options:
MASTER
SLAVE
*/

/*****************************************************************/

#define CLK_POLARITY			ONE_WHEN_IDLE
/*
you can select CLK_POLARITY from this options:
ZERO_WHEN_IDLE
ONE_WHEN_IDLE
Note: Slave must have the same ClocK Polarity
*/

/*****************************************************************/

#define CLK_PHASE			CAPTURE_DATA_2ND_TRANSITION
/*
you can select CLK_PHASE from this options:
CAPTURE_DATA_1ST_TRANSITION
CAPTURE_DATA_2ND_TRANSITION
Note: Slave must have the same ClocK Phase
*/

/*****************************************************************/

#define SPI1_BAUDRATE		FPCLK_DIV_BY_2
/*
you can select SPI1_BAUDRATE from this options:
FPCLK_DIV_BY_2
FPCLK_DIV_BY_4
FPCLK_DIV_BY_8
FPCLK_DIV_BY_16
FPCLK_DIV_BY_32
FPCLK_DIV_BY_64
FPCLK_DIV_BY_128
FPCLK_DIV_BY_256
*/

/*****************************************************************/


typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 CRCPR;
	volatile u32 RXCRCR;
	volatile u32 TXCRCR;
	
	volatile u32 I2SCFGR;
	volatile u32 I2SPR;
	
}SPIx_TypeDef;

#define 	SPI_1							((SPIx_TypeDef*)0x40013000)
#define 	SPI_2							((SPIx_TypeDef*)0x40003800)
#define 	SPI_3							((SPIx_TypeDef*)0x40003C00)


#define 	FRAME_FORMAT_8BIT				0
#define 	FRAME_FORMAT_16BIT				1

#define 	SOFTWARE_SLAVE_MANAGEMENT		0
#define 	HARWARE_SLAVE_MANAGEMENT		1

#define 	MSB								0
#define 	LSB								1

#define 	SLAVE							0
#define	 	MASTER							1

#define 	ZERO_WHEN_IDLE					0
#define 	ONE_WHEN_IDLE					1

#define		CAPTURE_DATA_1ST_TRANSITION		0
#define		CAPTURE_DATA_2ND_TRANSITION		1

											
#define 	FPCLK_DIV_BY_2				    0
#define 	FPCLK_DIV_BY_4                  1
#define 	FPCLK_DIV_BY_8                  2
#define 	FPCLK_DIV_BY_16                 3
#define 	FPCLK_DIV_BY_32                 4
#define 	FPCLK_DIV_BY_64                 5
#define 	FPCLK_DIV_BY_128                6
#define 	FPCLK_DIV_BY_256                7

typedef enum
{
	SPI1,
	SPI2,
	SPI3
}SPIx_t;
void SPI_voidInit(SPIx_t SPIx);
u8 	 SPI_u8SendReceiveSynch(SPIx_t SPIx, u8 u8DataToTransmit);
//void SPI_u8SendReceiveSynch(u8 Copy_u8DataToTransmit,u8 *Copy_DataToReceive);
//void SPI_voidSendReceiveAsynch(u8 Copy_u8DataToTransmit, void (*CallBack)(u8));




#endif
