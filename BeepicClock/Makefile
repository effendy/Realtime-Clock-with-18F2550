# MPLAB IDE generated this makefile for use with GNU make.
# Project: BeepicClock.mcp
# Date: Sun Apr 07 23:14:40 2019

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

BeepicClock.cof : ds3231.o my_i2c.o C18-BeepicLEDClock.o
	$(LD) /p18F2550 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.40\lib" "rm18f2550.lkr" "ds3231.o" "my_i2c.o" "C18-BeepicLEDClock.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"BeepicClock.cof" /M"BeepicClock.map" /W

ds3231.o : ds3231.c ../Program\ Files/Microchip/mplabc18/v3.47/h/stdio.h ../Program\ Files/Microchip/mplabc18/v3.47/h/stdlib.h ds3231.h my_i2c.h ds3231.c ../Program\ Files/Microchip/mplabc18/v3.47/h/stdarg.h ../Program\ Files/Microchip/mplabc18/v3.47/h/stddef.h
	$(CC) -p=18F2550 "ds3231.c" -fo="ds3231.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

my_i2c.o : my_i2c.c my_i2c.h my_i2c.c ../Program\ Files/Microchip/mplabc18/v3.47/h/p18cxxx.h ../Program\ Files/Microchip/mplabc18/v3.47/h/p18f2550.h
	$(CC) -p=18F2550 "my_i2c.c" -fo="my_i2c.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

C18-BeepicLEDClock.o : C18-BeepicLEDClock.c ../Program\ Files/Microchip/mplabc18/v3.47/h/delays.h ../Program\ Files/Microchip/mplabc18/v3.47/h/stdio.h my_i2c.h LiquidCrystal.h 18F2550BOLT.h ds3231.h C18-BeepicLEDClock.c ../Program\ Files/Microchip/mplabc18/v3.47/h/p18cxxx.h ../Program\ Files/Microchip/mplabc18/v3.47/h/p18f2550.h ../Program\ Files/Microchip/mplabc18/v3.47/h/stdarg.h ../Program\ Files/Microchip/mplabc18/v3.47/h/stddef.h
	$(CC) -p=18F2550 "C18-BeepicLEDClock.c" -fo="C18-BeepicLEDClock.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "ds3231.o" "my_i2c.o" "C18-BeepicLEDClock.o" "BeepicClock.cof" "BeepicClock.hex"

