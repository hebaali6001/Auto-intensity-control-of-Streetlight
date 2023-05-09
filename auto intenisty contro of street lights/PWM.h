

#ifndef PWM_H
#define	PWM_H
#include "config.h"
#include"lcd.h"

void pwm_init(void);
void pwm_set_duty(int duty);
void pwm_start(void);
void pwm_stop(void);



#endif	/* PWM_H */

