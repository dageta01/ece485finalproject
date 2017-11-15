/*
*********************************************************************************************************
*                                         BSP_JoyPosGet()
*
* Description : Return the joystick position.
*
* Argument(s) : none
*
* Return(s)   : The joystick postition.
*
*                        JOY_POS_LEFT    If the joystick is toggled left.
*                        JOY_POS_RIGHT   If the joystick is toggled right.
*                        JOY_POS_UP      If the joystick is toggled up.
*                        JOY_POS_DOWN    If the joystick is toggled down.
*                        JOY_POS_CENTER  If the joystick is being pressed
*                        JOY_POS_NONE    If the joystick is not being pressed.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
#include "LPC17xx.H"   
#include "mcb1700_joystick.h"


extern joystickpos JoyPosGet (void) 
{
	
	/*
	Isolates the pins for the joysticks up,down,left and right postions.
	They are `notted` because the pins are active low*	
	*/
	volatile	uint32_t stickStatus = ~(LPC_GPIO1->FIOPIN >> 23) & 0xF; 
	
	switch(stickStatus)
	{
		case 0x1: return JOY_POS_UP;
		case 0x2: return JOY_POS_RIGHT;
		case 0x4: return JOY_POS_DOWN;
		case 0x8: return JOY_POS_LEFT;
		default: break;
	}
	
	/*
	Checks to see if the center is pushed.
	This was done this way since the center 
	of the joystick is a lone wolf and doesn't 
	play well with others.
	*/
	if(~(LPC_GPIO1->FIOPIN >> 20) & 0x1)
	{
		return JOY_POS_CENTER;
	}
	else
	{
		return JOY_POS_NONE;
	}
	
}
extern joystickpos JoyPosSingle(void)
{
	/*
		Written to avoid having the joystick repeatedly
		input the same value.
	*/
	switch(JoyPosGet())
	{
		case JOY_POS_LEFT:
			while(JoyPosGet() == JOY_POS_LEFT);
			return JOY_POS_LEFT;
		case JOY_POS_DOWN:
			while(JoyPosGet() == JOY_POS_DOWN);
			return JOY_POS_DOWN;
		case JOY_POS_UP:
			while(JoyPosGet() == JOY_POS_UP);
			return JOY_POS_UP;
		case JOY_POS_RIGHT:
			while(JoyPosGet() == JOY_POS_RIGHT);
			return JOY_POS_RIGHT;
		case JOY_POS_CENTER:
			while(JoyPosGet() == JOY_POS_CENTER);
			return JOY_POS_CENTER;
		default:
			return JOY_POS_NONE;
	}
}
