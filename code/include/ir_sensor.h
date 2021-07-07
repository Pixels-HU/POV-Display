#ifndef _IR_SENSOR_H_
#define _IR_SENSOR_H_

/**
 * Select the IR GPIOx,PINx
 * for example :
 * #define 	IR_PIN							GPIOA,PIN1
 */
#define 	IR_PIN							GPIOB,PIN1
/* These is Remote Buttons */
typedef enum
{
	Button_POWER = 0	,
	Button_OK			,
	Button_RIGHT		,
	Button_LEFT			,
	Button_P_PLUS		,
	Button_P_MINUS 		,
	Button_VOL_PLUS		,
	Button_VOL_MINUS
}RemoteButton_t;

void IR_voidInit(void);
void IR_voidSetInterruptPin(EXTI_SelectPORTx_t IR_u8ExtiPort , EXTI_Line_t IR_u8ExtiLine );
void IR_voidSetCallBack(RemoteButton_t RemoteButton , void(*IR_PtrToFunc)(void) );



extern volatile u8  u8StartFlag    ;
extern volatile u32 u32Counter[50] ;
extern volatile u8  u8IndexCounter ;
extern volatile u8 Global_u8Flag   ;

// define it as a static
void IR_voidGetFrame(void);
void IR_voidReadFrame(void);
void _voidResetArrayElements(volatile u32 *arr , u8 size);
void voidTakeAction(u32 u32Decision);

#endif
