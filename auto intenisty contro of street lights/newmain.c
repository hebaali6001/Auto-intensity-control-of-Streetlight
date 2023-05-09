

#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "adc-lib.h"
#include "PWM.h"
#include "i2c.h"
#include "rtc_liberary.h"


unsigned char second, minute, hour, day, date, month, year;

char out[16];
int x;
int result;

void main(void) {

    OSCCON = 0x76;

    LCD_Initialize();
    I2C_Master_Init();
    pwm_init();
    ADC_init(1);

    RTC_WRITE_TIME(0, 00, 16, 3, 1, 3, 22);

    while (1) {
        
        RTC_READ_TIME(&second, &minute, &hour, &day, &date, &month, &year);
        result = ADC_start(0);

        if ((hour >= 7)&&(hour < 16)) {

            pwm_set_duty(0);
            LCDPutCmd(LCD_CLEAR);

            LCDGoto(4, 0);
            sprintf(out, "%2d : %2d", hour, minute);
            LCDPutStr(out);
            LCDGoto(5, 1);
            LCDPutStr("Morning");

        } else if (((hour >= 19)&&(hour <= 23)) || ((hour >= 0)&&(hour < 3))) {

            pwm_set_duty(500);
            LCDPutCmd(LCD_CLEAR);

            LCDGoto(4, 0);
            sprintf(out, "%2d : %2d", hour, minute);
            LCDPutStr(out);
            LCDGoto(5, 1);
            LCDPutStr("Night");

        } else if (((hour >= 3)&&(hour <= 7)) || ((hour >= 16)&&(hour < 19))) {
            GO_DONE = 1;
            if ((result > 0)&&(result < 500)) {

                pwm_set_duty(0);
                LCDPutCmd(LCD_CLEAR);

                LCDGoto(4, 0);
                sprintf(out, "%2d : %2d", hour, minute);
                LCDPutStr(out);
                LCDGoto(5, 1);
                LCDPutStr("Morning");

            } else if ((result > 500)&&(result < 600)) {

                pwm_set_duty(100);
                LCDPutCmd(LCD_CLEAR);

                LCDGoto(4, 0);
                sprintf(out, "%2d : %2d", hour, minute);
                LCDPutStr(out);
                LCDGoto(5, 1);
                LCDPutStr("M1");
            } else if ((result > 600)&&(result < 700)) {

                pwm_set_duty(225);
                LCDPutCmd(LCD_CLEAR);

                LCDGoto(4, 0);
                sprintf(out, "%2d : %2d", hour, minute);
                LCDPutStr(out);
                LCDGoto(5, 1);
                LCDPutStr("M2");
            } else if ((result > 700)&&(result < 800)) {

                pwm_set_duty(350);
                LCDPutCmd(LCD_CLEAR);

                LCDGoto(4, 0);
                sprintf(out, "%2d : %2d", hour, minute);
                LCDPutStr(out);
                LCDGoto(5, 1);
                LCDPutStr("M3");
            } else if (result > 800) {

                pwm_set_duty(500);
                LCDPutCmd(LCD_CLEAR);

                LCDGoto(4, 0);
                sprintf(out, "%2d : %2d", hour, minute);
                LCDPutStr(out);
                LCDGoto(5, 1);
                LCDPutStr("Night");
            }
        }
        while (GO_DONE);
        pwm_start();
    }
}

