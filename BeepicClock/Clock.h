#include "18F2550BOLT.h"
#include "my_i2c.h"
#include "ds3231.h"

/*Clock()
{
    init();
    SetTime( 1, 0, 0, true);
}*/

/*Clock(uint8_t hours, uint8_t minutes, uint8_t seconds, bool am)
{
    init();
    SetTime( hours, minutes, seconds, am);
}*/
long int _millis;
unsigned int _hasChanged;
unsigned int _am;
int _seconds;
int _minutes;
int _hours;
int _day;
int _date;
int _month;
int _year;
unsigned char hour_mode;
unsigned char time[10];
void RTC_read_time();

int millis(void)
{
	delay_ms(1);
	return _millis++;
}

void Clock_init(void)
{
    _millis = 0;
    _hasChanged = 1;
	//I2C_Initialize(32);

	_hours = 1; _minutes = 2; _seconds = 3;
}
/* seconds,minutes,hour,day,date,month,year variables will hold the 
   time and date values in BCD format */ 
 
void RTC_write_time(char seconds,char minutes,char hour,char day,char date,char month, char year)
{
    //I2C_Initialize(32);          /*start condition */
    
    //I2C_Write(0xD0);     /* slave address with write mode */
    //I2C_Write(0x00);     /* address of seconds register written to the pointer */ 
    
    //I2C_Write(seconds);  /*time register values */
    //I2C_Write(minutes);
    //I2C_Write(hour);
    
    //I2C_Write(day);      /*date registers */
    //I2C_Write(date);
    //I2C_Write(month);
    //I2C_Write(year);
    
    //I2C_End();          /*i2c stop condition */
}
void RTC_read_time()
{
    //I2C_Initialize(32);          /*start condition */
	 

    //I2C_Write(0xD0);     /* slave address with write mode */
    //I2C_Write(0x00);     /* address of seconds register written to the pointer */
    
    //I2C_Restart();
 
    //I2C_Write(0xD1);     /* slave address with read mode */
    hour_mode = DS3231_GetTime(time);
	
    //_seconds = I2C_Read(1);  /* Read the slave with ACK */
    //_minutes= I2C_Read(1);
    //_hours = I2C_Read(1);
    //_day = I2C_Read(1);
    //_date = I2C_Read(1);
    //_month = I2C_Read(1);
    //_year = I2C_Read(0);     /* Read the slave with not-ACK */
    
   /*Two things should be taken care of when reading the time
   the received values will be in **BCD format** and  after reading 
   the year register, a not-acknowledgement should be sent instead 
   of an acknowledgement */
   
    //I2C_End();          /*i2c stop condition */
}

void Clock_Update(int now)
{
    millis();
   /* if ((now - _millis) < 0) {
        // millis() wrapped around - it happens about every 50 days
        _millis = 0;
    }
    if ((_millis - now) >= 1000) {
        // A second has past since I last updated my values ... update again
        _millis = now;
        _seconds++;
        _hasChanged = 1;
        if (_seconds == 60) {
            // Carry over to minutes
            _seconds = 0;
            _minutes++;
            if (_minutes == 60) {
                // Carry over to hours
                _minutes = 0;
                _hours++;
                if (_hours == 12) {
                    // Toggle am
                    _am = !_am;
                } else if (_hours == 13) {
                    // Wrap back to 1:00
                    _hours = 1;
                }
            }
        }
    }*/
}

void SetTime( int hours, int minutes, int seconds, unsigned int am)
{
    _hours = hours;
    _minutes = minutes;
    _seconds = seconds;
    _am = am;
    _millis = millis();
}

/*long int modularDifference( long int a, long int n, long int m)
{
    long int an = (a-n)%m;
    long int na = (n-a)%m;
    if (abs(na) < abs(an)) {
        return na;
    }
    return an;
}

long int Clock_DifferenceInSeconds(Clock c)
{
    long int thisInSeconds = (_hours * 60 + _minutes) * 60 + _seconds;
    long int secondsIn12Hours = ((long int) 12) * ((long int) 3600);
    long int secondsIn24Hours = ((long int) 12) * ((long int) 3600);

    if (!_am) {
        thisInSeconds += secondsIn12Hours;
    }
    long int cInSeconds = (c._hours * 60 + c._minutes) * 60 + c._seconds;
    if (!c._am) {
        cInSeconds += secondsIn12Hours;
    }
    return modularDifference( thisInSeconds, cInSeconds, secondsIn24Hours);
}
*/


