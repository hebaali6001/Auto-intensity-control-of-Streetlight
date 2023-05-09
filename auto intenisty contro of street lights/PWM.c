
#include "PWM.h"
#include "config.h"
void pwm_init(void) {
    TRISC2 = 0;
    TMR2 = 0;
    PR2 = 124;
    T2CONbits.T2CKPS = 2;
    CCP1CONbits.CCP1M = 0xC;

}

void pwm_set_duty(int duty) { //1 TO  1023

    CCP1CONbits.DC1B = duty & 0b00000011;
    CCPR1L = duty >> 2;
}

void pwm_start(void) {
    TMR2ON = 1;
}

void pwm_stop(void) {
    TMR2ON = 0;

}
