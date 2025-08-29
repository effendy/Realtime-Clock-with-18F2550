/* 
 * File:   ds3231.h
 * Author: |H|e|c|t|o|r|
 *
 */

#ifndef DS3231_H
#define	DS3231_H

#define MODE_12HOUR_AM  0x40
#define MODE_12HOUR_PM  0X60
#define SECONDS         0x00
#define MINUTES         0x01
#define HOURS           0x02
#define DAY             0x03
#define DATE            0x04
#define MONTH           0x05
#define YEAR            0x06

//==============================================================================
// Function Prototypes.
//==============================================================================
void DS3231_AMPM(void);
void DS3231_HourMode(void);
void DS3231_AddData(unsigned char byte0);
void DS3231_GetCalendar(unsigned char *p1);
void DS3231_SetInfo(unsigned char byte0, unsigned char byte1);
unsigned char DS3231_GetTime(unsigned char *byte0);
unsigned char DS3231_GetHour(unsigned char *byte0);
unsigned char DS3231_GetInfo(unsigned char byte0);
unsigned char BCDToDecimal (unsigned char byte0);
unsigned char DecimalToBCD (unsigned char byte0);
unsigned char DS3231_SetTime(unsigned char hour, unsigned char minute, unsigned char second);
unsigned char DS3231_SetDate(unsigned char day, unsigned char month, unsigned char year);
#endif	/* DS3231_H */