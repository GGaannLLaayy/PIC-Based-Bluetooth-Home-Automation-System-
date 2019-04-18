/* 
 * File:   adc.h
 * Author: Mahendra
 *
 * Created on September 5, 2018, 4:37 AM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

void AD_set(void);
void ADC_init(void);
unsigned int AD_read(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

