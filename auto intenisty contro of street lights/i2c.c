#include "i2c.h"

void I2C_Master_Init() {

    SSPCON1 = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00; //////////// h7awl a3`yr l slew rate we ashof a a5bar
    SSPADD = (int)((_XTAL_FREQ / 4) / I2C_BaudRate) - 1;
    TRISC3 = 1;
    TRISC4 = 1;
}

void I2C_Slave_Init(unsigned char Address) {

    SSPADD = Address;
    SSPSTAT = 0x80;
    SSPCON1 = 0x36;
    SSPCON2 = 0x01;
    TRISC3 = 1;
    TRISC4 = 1;
    GIE = 1;
    PEIE = 1;
    SSPIF = 0;
    SSPIE = 1;
}

void I2C_Wait() {

    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Start() {

    I2C_Wait();
    SEN = 1;
}

void I2C_Stop() {

    I2C_Wait();
    PEN = 1;
}

void I2C_Restart() {

    I2C_Wait();
    RSEN = 1;
}

void I2C_ACK() {

    I2C_Wait();
    ACKDT = 0;
    ACKEN = 1;
}

void I2C_NACK() {

    I2C_Wait();
    ACKDT = 1;
    ACKEN = 1;
}

unsigned char I2C_Write( unsigned char Data) {
   
    I2C_Wait();
    SSPBUF = Data;
    I2C_Wait();
    return ACKSTAT;
}

unsigned char I2C_Read() {
 I2C_Wait();
    RCEN = 1;
    while (!SSPIF);
    SSPIF = 0;
    return SSPBUF;
}

void interrupt ISRead() {

    if (SSPIF) {
        if (!R_nW) ///////////////////////////
        {
            char Dummy = SSPBUF;
            CKP = 1;
            while (!BF);
            //RX_Data = SSPBUF;
        }
        CKP = 1;
        SSPIF = 0;
    }
}

void interrupt ISWrite() {

    if (SSPIF) {
        if (R_nW) {
            char deummy = SSPBUF;
            BF = 0;
           // SSPBUF = TX_Data;
            CKP = 1;
            while (BF);

        }
        CKP = 1;
        SSPIF = 0;
    }
}