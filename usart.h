/* 
 * File:   usart.h
 * Author: Mahendra
 *
 * Created on September 5, 2018, 4:38 AM
 */

#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif
void serial_init(void);
    void serial_println(const char *buffer);
    void serial_print(const char *buffer);
    void serial_write(char data);



#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

