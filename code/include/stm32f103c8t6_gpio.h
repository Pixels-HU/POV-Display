/**
 * @Author					:			John Atia Nafady
 * @Date					: 			20-5-2021
 * @Version					:			V02
 */

#ifndef _GPIO_H_
#define _GPIO_H_


typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIOx_TypeDef;

#define GPIOA_BASE_ADDress				0x40010800
#define GPIOB_BASE_ADDress				0x40010C00
#define GPIOC_BASE_ADDress				0x40011000
#define GPIO_A							((GPIOx_TypeDef*)GPIOA_BASE_ADDress)
#define GPIO_B							((GPIOx_TypeDef*)GPIOB_BASE_ADDress)
#define GPIO_C							((GPIOx_TypeDef*)GPIOC_BASE_ADDress)

typedef enum
{
	GPIOA,
	GPIOB,
	GPIOC
}GPIOx_t;
typedef enum
{
	PIN0	  ,
	PIN1      ,
	PIN2      ,
	PIN3      ,
	PIN4      ,
	PIN5      ,
	PIN6      ,
	PIN7      ,
	PIN8      ,
	PIN9      ,
	PIN10     ,
	PIN11     ,
	PIN12     ,
	PIN13     ,
	PIN14     ,
	PIN15
}GPIO_PINx_t;

typedef enum
{
	LOW,
	HIGH
}GPIO_OutLevel_t;
/* Modes & Configurations */
typedef enum
{
	/* For INPUT 																*/
	IN_ANALOG 			= 0b0000 ,
	IN_FLOATING 		= 0b0100 ,
	IN_PULLUP_PULLDOWN 	= 0b1000 ,
	/* For General Purpose OUTPUT, there're Push-Pull & Open_Drain				*/
	OUT_PUSHPULL_10MHz 	= 0b0001 ,
	OUT_PUSHPULL_2MHz 	= 0b0010,
	OUT_PUSHPULL_50MHz 	= 0b0011 ,
	/* Remains Alternate Function OUTPUT, there're Push-Pull & Open_Drain		*/
	ALTRNATIVE_FUNC_PUSHPULL = 0b1011
}GPIO_Mode_t;



void GPIO_voidSetPinDir(GPIOx_t GPIOx, GPIO_PINx_t GPIO_PINx, GPIO_Mode_t GPIO_Mode);
void GPIO_voidSetPinValue(GPIOx_t GPIOx, GPIO_PINx_t GPIO_PINx, GPIO_OutLevel_t GPIO_OutLevel);
u8   GPIO_u8GetPinValue(GPIOx_t GPIOx, GPIO_PINx_t GPIO_PINx);


#endif
