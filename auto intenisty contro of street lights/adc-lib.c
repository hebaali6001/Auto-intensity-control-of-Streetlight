
#include"adc-lib.h"
#include "config.h"

void ADC_init(char ch_no) {
    
    ADCON1bits.VCFG = 0;
    ADCON1bits.PCFG = 15 - ch_no;
    ADFM = 1;
    ADON = 1;
    
}

int ADC_start(char ANx) {
    
    ADCON0bits.CHS = ANx;
    return ADRES;
    
}

//GO_DONE = x;         //0 or 1

