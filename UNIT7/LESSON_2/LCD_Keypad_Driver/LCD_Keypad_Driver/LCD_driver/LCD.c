/*
 * LCD.c
 *
 * Created: 15/07/2024 11:36:12 AM
 *  Author: Mahmoud
 */ 


#include "LCD.h"

static int cursor_pos = 0;
void LCD_INIT()
{
	_delay_ms(20);
	SET_BIT(CTRL_DIR_LCD,RS_SWITCH);
	SET_BIT(CTRL_DIR_LCD,RW_SWITCH);
	SET_BIT(CTRL_DIR_LCD,EN_SWITCH);
	CLEAR_BIT(LCD_CTRL,RS_SWITCH);
	CLEAR_BIT(LCD_CTRL,RW_SWITCH);
	CLEAR_BIT(LCD_CTRL,EN_SWITCH);
	DATA_DIR_LCD = 0xFF;
	LCD_CLEAR();
	#ifdef EIGHT_BIT_MODE
		LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	
	#ifdef FOUR_BIT_MODE
		LCD_WRITE_COMMAND(0x02);
		LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif
	
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR);
}

void LCD_WRITE_COMMAND(unsigned char command)
{
	#ifdef EIGHT_BIT_MODE
		LCD_PORT = command;
		CLEAR_BIT(LCD_CTRL,RW_SWITCH);
		CLEAR_BIT(LCD_CTRL,RS_SWITCH);
		LCD_KICK();
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	CLEAR_BIT(LCD_CTRL,RW_SWITCH);
	CLEAR_BIT(LCD_CTRL,RS_SWITCH);
	LCD_KICK();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	CLEAR_BIT(LCD_CTRL,RW_SWITCH);
	CLEAR_BIT(LCD_CTRL,RS_SWITCH);
	LCD_KICK();
	#endif
}

void LCD_WRITE_CHAR(unsigned char character)
{
	if(cursor_pos==16)
	{
		LCD_MOVE_CURSOR(2,0);
	}
	if(cursor_pos==32)
	{
		LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
		LCD_MOVE_CURSOR(1,0);
		cursor_pos=0;
	}
	cursor_pos++;
	
	#ifdef EIGHT_BIT_MODE
		SET_BIT(LCD_CTRL,RS_SWITCH);
		LCD_PORT = character;
		CLEAR_BIT(LCD_CTRL,RW_SWITCH);
		SET_BIT(LCD_CTRL,RS_SWITCH);
		LCD_KICK();
	#endif
	
	#ifdef FOUR_BIT_MODE
		LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
		SET_BIT(LCD_CTRL,RS_SWITCH);
		CLEAR_BIT(LCD_CTRL,RW_SWITCH);
		LCD_KICK();
		LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
		SET_BIT(LCD_CTRL,RS_SWITCH);
		CLEAR_BIT(LCD_CTRL,RW_SWITCH);
		LCD_KICK();
	#endif
}


void LCD_WRITE_STRING(const char *str)
{
	while(*str!='\0')
	{
		LCD_WRITE_CHAR(*str++);
	}
}

void LCD_CHECK_BUSY()
{
	#ifdef EIGHT_BIT_MODE
	DATA_DIR_LCD = 0x00;
	#endif
	
	#ifdef FOUR_BIT_MODE
	DATA_DIR_LCD = 0x0F;
	#endif
	
	SET_BIT(LCD_CTRL,RW_SWITCH);
	CLEAR_BIT(LCD_CTRL,RS_SWITCH);
	LCD_KICK();
	DATA_DIR_LCD = 0xFF;
	CLEAR_BIT(LCD_CTRL,RW_SWITCH);
}

void LCD_KICK()
{
	SET_BIT(LCD_CTRL,EN_SWITCH);
	_delay_ms(50);
	CLEAR_BIT(LCD_CTRL,EN_SWITCH);
}

void LCD_CLEAR()
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
	cursor_pos = 0;
	LCD_MOVE_CURSOR(1,0);
}

void LCD_MOVE_CURSOR(unsigned char line, unsigned char position)
{
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
			cursor_pos = position;
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
			cursor_pos = position+16;
		}
	}
}


void LCD_CUSTOM_CHAR(void)
{
	LCD_WRITE_COMMAND(64);
	LCD_WRITE_CHAR(0);
	LCD_WRITE_CHAR(14);
	LCD_WRITE_CHAR(17);
	LCD_WRITE_CHAR(2);
	LCD_WRITE_CHAR(4);
	LCD_WRITE_CHAR(4);
	LCD_WRITE_CHAR(0);
	LCD_WRITE_CHAR(4);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_CHAR(0);
}