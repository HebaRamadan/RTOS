/*
 * Lcd_int.h
 *
 *  Created on: Jul 18, 2020
 *      Author: zas
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

#define LCD_u8CMD_DISP_ON_CURS_OFF    0x0C
#define LCD_u8CMD_8_BIT_2x16_5x7      0x38
#define LCD_u8CMD_CLR_Display         0x01
#define LCD_QUEUE_NULL                    0xff


void Lcd_vidInit(void);
void Lcd_vidSendCommand(u8 Cmd);
void Lcd_vidWriteChar(u8 Char);
void Lcd_vidEnableTrigger(void);
void Lcd_vidDisableTrigger(void);


void Lcd_vidQueueChar(u8 Char);
void Lcd_vidQueueCommand(u8 Command);
void Lcd_vidQueueString(u8 *Str);
void Lcd_vidClearQueue(void);
u8   Lcd_u8ReadQueue(void);

#endif /* LCD_INT_H_ */
