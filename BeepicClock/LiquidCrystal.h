#ifndef LiquidCrystal_h
#define LiquidCrystal_h

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00



void LiquidCrystal(unsigned int rs, unsigned int enable,
		unsigned int d0, unsigned int d1, unsigned int d2, unsigned int d3);

  void init(unsigned int fourbitmode,unsigned int rs,unsigned int rw,unsigned int enable,
	   unsigned int d0,unsigned int d1,unsigned int d2,unsigned int d3,
	   unsigned int d4,unsigned int d5,unsigned int d6,unsigned int d7);
    
  void begin(unsigned int cols,unsigned int rows,unsigned int charsize);

  void clear();
  void home();

  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();

  void setRowOffsets(int row1, int row2, int row3, int row4);
  void createChar(unsigned int,unsigned int[]);
  void setCursor(unsigned int,unsigned int); 
  void command(unsigned int);
  

  void send(unsigned int,unsigned int);
  void write4bits(unsigned int);
  void write8bits(unsigned int);
  void pulseEnable();

 unsigned int _rs_pin; // LOW: command.  HIGH: character.
 unsigned int _rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
 unsigned int _enable_pin; // activated by a HIGH pulse.
 unsigned int _data_pins[8];

 unsigned int _displayfunction;
 unsigned int _displaycontrol;
 unsigned int _displaymode;

 unsigned int _initialized;

 unsigned int _numlines;
 unsigned int _row_offsets[4];


#endif