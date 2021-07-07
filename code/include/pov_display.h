/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				19 MAR 2021									*/
/*	Version					: 				V03											*/
/*	File					:				PovDisplay_interface.h																			*/
/*																						*/
/****************************************************************************************/

#ifndef	_POV_DISPLAY_H_
#define _POV_DISPLAY_H_

extern volatile u16 	CurrentDistanceBetweenTeeth;
extern volatile s8		ArrowCounter;
extern volatile u8 		ArrowFlag;

/***********************************************************************************
 * 									Global Arrays                                  *
 ***********************************************************************************/
extern u16 POV_u16ShortArrow[5];
extern u16 POV_u16LongArrow[5];
extern u16 POV_u16Num1[3];
extern u16 POV_u16Num2[4];
extern u16 POV_u16Num3[7];
extern u16 POV_u16Num6[4];
extern u16 POV_u16Num9[7];
extern u16 MIX[5];
extern u16 POV_u16PIXELS[30];
extern u16 POV_u16WE[14];
extern u16 POV_u16ARE[17];
extern u16 POV_u16LEARN[29];
extern u16 POV_u16MAKE[25];
extern u16 POV_u16SHARE[28];
extern u16 POV_u16THANKS[36];
extern u16 POV_u16TREND[];



void POV_DisplayMinutes(u8 NumOfMinutes , u16 DistanceBetweenthem );
void POV_DisplayClock(void);
void POV_DisplayWord(u16 *Word , u16 SizeOfWord);




#endif




