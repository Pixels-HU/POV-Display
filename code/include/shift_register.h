/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				28 OCT 2020									*/	
/*	Version					: 				V01											*/	
/*																						*/
/*																						*/
/****************************************************************************************/

#ifndef _SHIFT_REGISTER_H_
#define _SHIFT_REGISTER_H_

#define		S2P_SERIAL_DATA			GPIOA,0
#define		S2P_STORAGE_CLK			GPIOA,1
#define		S2P_SHIFT_CLK			GPIOA,2



void S2P_voidSend8BitSynchronous(u8 u8Data);
void S2P_voidSend16BitSynchronous(u16 u16Data);

#endif
