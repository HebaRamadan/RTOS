/*
 * Lcd_cfg.h
 *
 *  Created on: Jul 18, 2020
 *      Author: zas
 */
#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define CHAR     0
#define COMMAND  1

#define MAXIMUM_ELEMENT_IN_QUEUE      50


#define LCD_u8RS_PIN DIO_u8PIN_0      //RS at PORTA PIN_0
#define LCD_u8RW_PIN DIO_u8PIN_1	  //RW at PORTA PIN_0
#define LCD_u8EN_PIN DIO_u8PIN_2	  //EN at PORTA PIN_0

#define LCD_u8D0_PIN DIO_u8PIN_24	  //D0 at PORTD PIN_0
#define LCD_u8D1_PIN DIO_u8PIN_25	  //D1 at PORTD PIN_1
#define LCD_u8D2_PIN DIO_u8PIN_26	  //D2 at PORTD PIN_2
#define LCD_u8D3_PIN DIO_u8PIN_27	  //D3 at PORTD PIN_3
#define LCD_u8D4_PIN DIO_u8PIN_28	  //D4 at PORTD PIN_4
#define LCD_u8D5_PIN DIO_u8PIN_3	  //D5 at PORTA PIN_3
#define LCD_u8D6_PIN DIO_u8PIN_30	  //D6 at PORTD PIN_6
#define LCD_u8D7_PIN DIO_u8PIN_4	  //D7 at PORTA PIN_4

#endif /* LCD_CFG_H_ */
