/*
 * Timer1_priv.h
 *
 *  Created on: Aug 5, 2020
 *      Author: zas
 */

#ifndef RTOS_TIMER1_PRIV_H_
#define RTOS_TIMER1_PRIV_H_


/*
 * Timer 1 Interrupt Vectors
 */

#define TIMER1_CAPT_vect       __vector_6
#define TIMER1_COMPA_vect      __vector_7
#define TIMER1_COMPB_vect      __vector_8
#define TIMER1_OVF_vect        __vector_9

/*
 * General Timer registers
 */
#define TIMSK        (*(volatile u8*) 0x59)
#define SREG         (*(volatile u8*) 0x5F)



/*
 * Timer 1 Registers
 */

#define TCCR1A        (*(volatile u8*)(0x4F))
#define TCCR1B        (*(volatile u8*)(0x4E))
#define TCCR1         (*(volatile u8*)(0x4E))
#define TCNT1H        (*(volatile u8*)(0x4D))
#define TCNT1L        (*(volatile u8*)(0x4C))
#define TCNT1         (*(volatile u8*)(0x4C))
#define OCR1AH        (*(volatile u8*)(0x4B))
#define OCR1AL        (*(volatile u8*)(0x4A))
#define OCR1A         (*(volatile u8*)(0x4A))
#define OCR1BH        (*(volatile u8*)(0x4F))
#define OCR1BL        (*(volatile u8*)(0x48))
#define OCR1B         (*(volatile u8*)(0x48))
#define ICR1H         (*(volatile u8*)(0x47))
#define ICR1L         (*(volatile u8*)(0x46))
#define ICR1          (*(volatile u8*)(0x46))


#endif /* RTOS_TIMER1_PRIV_H_ */
