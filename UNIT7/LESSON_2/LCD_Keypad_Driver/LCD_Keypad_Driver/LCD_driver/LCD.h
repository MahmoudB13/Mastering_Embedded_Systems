/*
 * LCD.h
 *
 * Created: 15/07/2024 11:36:22 AM
 *  Author: Mahmoud
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <xc.h>
#include "../UTILS.h"

#define LCD_PORT PORTA
#define DATA_DIR_LCD DDRA

#define LCD_CTRL PORTB
#define CTRL_DIR_LCD DDRB

#define RS_SWITCH 1
#define RW_SWITCH 2
#define EN_SWITCH 3
#define DATA_SHIFT 4

//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE

#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)


void LCD_INIT();
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char character);
void LCD_WRITE_STRING(const char* string);
void LCD_CHECK_BUSY(void);
void LCD_KICK(void);
void LCD_CLEAR();
void LCD_MOVE_CURSOR(unsigned char line, unsigned char position);
void LCD_CUSTOM_CHAR(void);

#endif /* LCD_H_ */