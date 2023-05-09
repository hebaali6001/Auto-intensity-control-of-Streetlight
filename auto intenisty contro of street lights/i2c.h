/* 
 * File:   i2c.h
 * Author: islam
 *
 * Created on January 15, 2022, 10:28 PM
 */

#ifndef I2C_H
#define	I2C_H

#include "config.h"

#define I2C_BaudRate 1e5

void I2C_Master_Init(void);
void I2C_Slave_Init(unsigned char Address);
void I2C_Wait(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_ACK(void);
void I2C_NACK(void);
unsigned char I2C_Write(unsigned char Data);
unsigned char I2C_Read(void);
void interrupt ISRead(void);
void interrupt ISWrite(void);


#endif

