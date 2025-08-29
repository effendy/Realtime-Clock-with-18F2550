/*Test program for Bolt 18F2550. Flash 
LED RB0 with 500 ms delay.*/

#include <p18cxxx.h>
#include <delays.h>
#include <stdio.h>
#include "my_i2c.h"
#include "18F2550BOLT.h"
//#include "LiquidCrystal.h"
#include "ds3231.h"


/** P R I V A T E  P R O T O T Y P E S ***************************************/
extern void _startup( void ); // See c018i.c in your C18 compiler dir 
#pragma code _RESET_INTERRUPT_VECTOR = 0x001000 
void _reset( void ) 
{ 
    _asm goto _startup _endasm 
} 
#pragma code
int i;
long int now;
unsigned char led;
int thisChar = 0;
unsigned char rim[10];
unsigned char hour_mode;
unsigned char time[10];
int _seconds;
int _minutes;
int _hours;
int _day;
int _date;
int _month;
int _year;
long int _millis;
unsigned char Switch = 0;
unsigned char Switch2 = 0;
unsigned char Mode = 0;
unsigned char debounceDelay = 200;

unsigned char debounce (unsigned char port){
	static int state = 0;
	state = (state << 1) | ((microsw() & port)) | 0xfe00;
	return(state == 0xff00);
}
unsigned char debounce2 (unsigned char port){
	static int state = 0;
	state = (state << 1) | ((microsw() & port)) | 0xfe00;
	return(state == 0xff00);
}


void main()
{
	init_bolt();
	
	//Clock_init();
	I2C_Close();
	I2C_Init(39);
	LiquidCrystal(RA1, RA2, RB0, RB1, RB2, RB3); //rs = RC6, EN = RC7
 	begin(16, 2,LCD_5x8DOTS);
	clear();
	rightToLeft();
	Switch = 0x01;
	Switch2 = 0x02;
	Mode = 0;

// print from 0 to 9:
  	/*for(thisChar =0;thisChar<10;thisChar++){
    	write(thisChar+0x30);
    	delay_ms(500);
		cursor();
		blink();
	}*/
	//clear();
	// uncomment the following to set the date and time
	//DS3231_SetDate(15,8,25);
	//DS3231_SetTime(00,05,01);

	//now = _millis;
	now = 0;
malla:
	setCursor(0, 0);
	DS3231_GetCalendar(rim);
	PrintString(rim);

	setCursor(0,1);
	hour_mode = DS3231_GetTime(time);
	PrintString(time);
	if (debounce(Switch) & 0x01 == 0x01 ) {
	  if (((microsw() & Switch) == 0)){
		//Delay10TCYx(25*100);
		//if ((microsw() & Switch) == 0){
		switch (Mode){
		  case 0: DS3231_AddData(HOURS); break;
		  case 1: DS3231_AddData(MINUTES); break;
		  case 2: DS3231_AddData(DAY); break;
		  case 3: DS3231_AddData(DATE); break;
	 	  case 4: DS3231_AddData(MONTH); break;
		}
	  }
	}
	if(debounce2(Switch2) & 0x01 == 0x1){
		  if (Mode < 5)	{
		 	Mode++;
		  }
		  else Mode = 0;
	}
	//setCursor(0,0);
	//sprintf(rim, (const far rom char*)"%2d:%2d:%2d",_hours,_minutes,_seconds);
	//PrintString(rim);
	
	write(32);
	goto malla;

}



