#ifndef _JOYSTICK
#define _JOYSTICK

/*
	Header file for the mcb1700 joystick controller. 
*/
typedef enum
{
	JOY_POS_LEFT,
	JOY_POS_RIGHT,
	JOY_POS_UP,
	JOY_POS_DOWN,
	JOY_POS_CENTER,
	JOY_POS_NONE
}joystickpos;


extern joystickpos JoyPosGet(void);
extern joystickpos JoyPosSingle(void);
#endif
