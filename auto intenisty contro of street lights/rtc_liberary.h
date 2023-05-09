

#ifndef RTC_LIBERARY_H
#define	RTC_LIBERARY_H

#include"i2c.h"




unsigned char decimel_to_bcd(unsigned char num);

unsigned char bcd_to_decimel(unsigned char num);

void RTC_WRITE_TIME(unsigned char second,unsigned char minute,unsigned char hour,unsigned char day,
        unsigned char date,unsigned char month,unsigned char year);

void RTC_READ_TIME(unsigned char* second,unsigned char* minute,unsigned char* hour,unsigned char* day,
        unsigned char* date,unsigned char* month,unsigned char* year);


#endif	/* RTC_LIBERARY_H */

