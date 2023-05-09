#include "rtc_liberary.h"

unsigned char decimel_to_bcd(unsigned char num) {

    return (((num / 10) << 4)+(num % 10));
}

unsigned char bcd_to_decimel(unsigned char num) {

    return (((num >> 4)*10)+(num & 0x0f));
}

void RTC_WRITE_TIME(unsigned char second, unsigned char minute, unsigned char hour, unsigned char day,
        unsigned char date, unsigned char month, unsigned char year) {

    second = decimel_to_bcd(second);
    minute = decimel_to_bcd(minute);
    hour = decimel_to_bcd(hour);
    day = decimel_to_bcd(day);
    date = decimel_to_bcd(date);
    month = decimel_to_bcd(month);
    year = decimel_to_bcd(year);

    I2C_Start();

    I2C_Write(0XD0);
    I2C_Write(0X00);

    I2C_Write(second);
    I2C_Write(minute);
    I2C_Write(hour);
    I2C_Write(day);
    I2C_Write(date);
    I2C_Write(month);
    I2C_Write(year);

    I2C_Stop();

}

void RTC_READ_TIME(unsigned char* second, unsigned char* minute, unsigned char* hour, unsigned char* day,
        unsigned char* date, unsigned char* month, unsigned char* year) {


    I2C_Start();

    I2C_Write(0XD0);
    I2C_Write(0X01);

    I2C_Restart();

    I2C_Write(0XD1);

    *second = I2C_Read();
    I2C_ACK();
    *minute = I2C_Read();
    I2C_ACK();
    *hour = I2C_Read();
    I2C_ACK();
    *day = I2C_Read();
    I2C_ACK();
    *date = I2C_Read();
    I2C_ACK();
    *month = I2C_Read();
    I2C_ACK();
    *year = I2C_Read();
    I2C_NACK();

    *second = bcd_to_decimel(*second);
    *minute = bcd_to_decimel(*minute);
    *hour = bcd_to_decimel(*hour);
    *day = bcd_to_decimel(*day);
    *date = bcd_to_decimel(*date);
    *month = bcd_to_decimel(*month);
    *year = bcd_to_decimel(*year);
    
I2C_Stop();

}