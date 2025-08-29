#include "LiquidCrystal.h"
//LIBRERIA UNIVERSAL PARA EL SISTEMA BOLT 20 MHZ

//DEFINICIONES DE PINES:

//#define RELE PORTAbits.RA0
#define SW1  PORTCbits.RC0
#define SW2  PORTCbits.RC1
//#define SW3  PORTCbits.RC0
//#define SW4  PORTCbits.RC1
#define RA0  PORTAbits.RA0
#define RA1  PORTAbits.RA1	
#define RA2  PORTAbits.RA2
#define RA3  PORTAbits.RA3	
#define RB0  PORTBbits.RB0
#define RB1  PORTBbits.RB1
#define RB2  PORTBbits.RB2
#define RB3  PORTBbits.RB3
#define RB4  PORTBbits.RB4
#define RB5  PORTBbits.RB5
#define RB6  PORTBbits.RB6
#define RB7  PORTBbits.RB7
#define RC6  PORTCbits.RC6
#define RC7  PORTCbits.RC7
#define delay_us	Delay10TCYx

//FUNCIONES DISPONIBLES:

void writeeeprom(unsigned char addr,unsigned char byte);  //escribe un dato en la EEPROM
unsigned char readeeprom(unsigned char addr); //lee un dato de la EEPROM
void init_bolt(void); //inicializa puertos leds y microswitches en BOLT
int microsw(void);	//lee los microswitches, la función toma el valor de 0...15
void delay_ms(int i); //delay parámetro en milisegundos (i<32000)
void EnableLCD(void);	//pulso de escritura
void EnableLCD2(void);	//pulso de escritura
void InitLCD(void);	//inicializa LCD
void ClearScreen(void); //borra LCD
void GotoXY(unsigned char r, unsigned char c);	//posiciona cursor en celda seleccionada
void PutLCD(char c);	//escribe caracter en LCD parámetro en ASCII
void PrintString(const char* s);	//escribe string hasta 8 caracteres. Parámetro es el string.
unsigned char GetBot(void);		//lee 1 caracter del teclado. La función regresa con el valor ASCII de la tecla.
void fin(void);
void SetBot(void);			//lee un string del teclado terminando con "F". Lo guarda en el arreglo "bot[]"
void row(void);
void WrtBot(void);			//escribe el string almacenado en el arreglo "bot[]" en el LCD. 
unsigned char Set7Seg(int i);	// Convert int to 7 Seg output
//función también disponible: delay_us(); parámetro <250.

void delay_ms(int i)
{
	long int j;
	for(j=0;j<i;j++)
	{
	Delay1KTCYx(12); 	//A 20 MHZ, 1 MS APROX.
	}
}

unsigned char Set7Seg(int i)
{
	unsigned char Output;
	switch (i){
		case 0: Output = 0x3F; break;
		case 1: Output = 0x06; break;
		case 2: Output = 0x5B; break;
		case 3: Output = 0x4F; break;
		case 4: Output = 0x66; break;
		case 5: Output = 0x6D; break;
		case 6: Output = 0x7D; break;
		case 7: Output = 0x07; break;
		case 8: Output = 0x7F; break;
		case 9: Output = 0x6F; break;
	}
	return ~Output; 
}
//INICIALIZA LOS PUERTOS A, B Y C
void init_bolt(void)
{
ADCON1=0x0F; 	//Configure A/D
CMCON=7;		// configure comparators for digital Input
TRISB=0x03;		//RB0, RB1 as input rest PORTB as output
//TRISA=0X30;		//RA4,RA5 SON ENTRADAS (MICROSWITCHES). RA0,RA1,RA2,RA3 SON SALIDAS
TRISA=0x30;		//PORTA(RA5, RA4 as Input) (RA3, RA2, RA1, RA0 as output)
PORTA=0xFF;
TRISC=0X0F;		//RC0,RC1 SON ENTRADAS (MICROSWITCHES) RC6= LCD->RS, RC7 = LCD->EN
INTCON2bits.RBPU=0;	//SELECCIONA RESISTENCIAS DE PULL UP EN PUERTO B (RB4...RB7).
RB4=0; // turn of the BEEPIC programming LED
RB5=0;

}

/*MICROSWITCHES*/
//LEE LOS MICROSWITCHES. REGRESA CON UN VALOR DE 0...15.
int microsw(void)
{
int i;
i=(SW1*1)+(SW2*2);
return i;
}


/*LCD*/
// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1 
//    S = 0; No shift 
void EnableLCD(void) {

    RC6=0; delay_us(50);  //RS= 0
    RC7=1; delay_us(50);  //E = 1
    RC7=0; delay_us(50);  //E = 0

}

void EnableLCD2(void) {

    RC6=1;  delay_us(50);	//RS=1
    RC7=1;  delay_us(50);	//E =1
    RC7=0;  delay_us(50);	//E =0
}
void LiquidCrystal(unsigned int rs, unsigned int enable,
		unsigned int d0, unsigned int d1, unsigned int d2, unsigned int d3){
  init(1, rs, 255, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

 void init(unsigned int fourbitmode,unsigned int rs,unsigned int rw,unsigned int enable,
	   unsigned int d0,unsigned int d1,unsigned int d2,unsigned int d3,
	   unsigned int d4,unsigned int d5,unsigned int d6,unsigned int d7)
{
  _rs_pin = rs;
  _rw_pin = rw;
  _enable_pin = enable;
  
  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3; 
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7; 

  if (fourbitmode)
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  else 
    _displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
  
  begin(16, 1, LCD_5x8DOTS);  
}
/********** high level commands, for the user! */
void clear(){
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delay_us(2000);  // this command takes a long time!
}
void home()
{
  command(LCD_RETURNHOME);  // set cursor position to zero
  delay_us(2000);  // this command takes a long time!
}
// Turn the display on/off (quickly)
void noDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
// Turns the underline cursor on/off
void noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void cursor() {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
// Turn on and off the blinking cursor
void noBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void blink() {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
// These commands scroll the display without changing the RAM
void scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}
// This is for text that flows Left to Right
void leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}
// This will 'right justify' text from the cursor
void autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

void setCursor(unsigned int col, unsigned int row)
{
  const int max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
 
  if ( row >= max_lines ) {
    row = max_lines - 1;    // we count rows starting w/0
  }
  if ( row >= _numlines ) {
    row = _numlines - 1;    // we count rows starting w/0
  }
  
  command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

void setRowOffsets(int row0, int row1, int row2, int row3)
{
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}
void begin(unsigned int cols,unsigned int rows,unsigned int charsize){
  if (rows > 1) {
    _displayfunction |= LCD_2LINE;
  }
  _numlines = rows;

  setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);  

  // for some 1 line displays you can select a 10 pixel high font
  if ((charsize != LCD_5x8DOTS) && (rows == 1)) {
    _displayfunction |= LCD_5x10DOTS;
  }
   //pinMode(_rs_pin, OUTPUT);
  // we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
  if (_rw_pin != 255) { 
   // pinMode(_rw_pin, OUTPUT);
  }
  //pinMode(_enable_pin, OUTPUT);
  
  // Do these once, instead of every time a character is drawn for speed reasons.
  /*for (int i=0; i<((_displayfunction & LCD_8BITMODE) ? 8 : 4); ++i)
  {
    pinMode(_data_pins[i], OUTPUT);
   }*/ 

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
  delay_us(50000); 
  // Now we pull both RS and R/W low to begin commands
  //digitalWrite(_rs_pin, LOW);
   RC6=0; delay_us(50);  //RS= 0  
  //digitalWrite(_enable_pin, LOW);
   RC7=0; delay_us(50);  //E = 0
  if (_rw_pin != 255) { 
  //  digitalWrite(_rw_pin, LOW);
  }
  
  //put the LCD into 4 bit or 8 bit mode
  if (! (_displayfunction & LCD_8BITMODE)) {
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    write4bits(0x03);
    delay_us(4500); // wait min 4.1ms

    // second try
    write4bits(0x03);
    delay_us(4500); // wait min 4.1ms
    
    // third go!
    write4bits(0x03); 
    delay_us(150);

    // finally, set to 4-bit interface
    write4bits(0x02); 
  } else {
    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    command(LCD_FUNCTIONSET | _displayfunction);
    delay_us(4500);  // wait more than 4.1ms

    // second try
    command(LCD_FUNCTIONSET | _displayfunction);
    delay_us(150);

    // third go
    command(LCD_FUNCTIONSET | _displayfunction);
  }

  // finally, set # lines, font size, etc.
  command(LCD_FUNCTIONSET | _displayfunction);  

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
  display();

  // clear it off
  clear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);

}

/*********** mid level commands, for sending data/cmds */
void command(unsigned int value) {
  send(value, 0);
}
int write(unsigned int value) {
  send(value, 1);
  return 1; // assume sucess
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void createChar(unsigned int location, unsigned int charmap[]) {
  int i;  
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  
  for (i=0; i<8; i++) {
    write(charmap[i]);
  }
}
/************ low level data pushing commands **********/
// write either command or data, with automatic 4/8-bit selection
void send(unsigned int value, unsigned int mode) {
  //digitalWrite(_rs_pin, mode);
  RC6=mode; delay_us(50);  //RS= mode
  // if there is a RW pin indicated, set it low to Write
  if (_rw_pin != 255) { 
    //digitalWrite(_rw_pin, LOW);
  }
  
  if (_displayfunction & LCD_8BITMODE) {
    write8bits(value); 
  } else {
    write4bits(value>>4);
    write4bits(value);
  }
}
void pulseEnable(void) {
  //digitalWrite(_enable_pin, LOW);
  RC7=0; delay_us(1);  //E = 0    
  //digitalWrite(_enable_pin, HIGH);
  RC7=1; delay_us(10);  //E = 1       // enable pulse must be >450ns
  //digitalWrite(_enable_pin, LOW);
  RC7=0; delay_us(100);  //E = 0       // commands need > 37us to settle
}
void write4bits(unsigned int value) {
  /*for (int i = 0; i < 4; i++) {
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
  }*/
  RA0 = (value) & 0x01; 
  RA1 = (value >> 1) & 0x01; 
  RA2 = (value >> 2) & 0x01; 
  RA3 = (value >> 3) & 0x01; 
  pulseEnable();
}
void write8bits(unsigned int value) {
  /*for (int i = 0; i < 8; i++) {
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
  }*/
  
  pulseEnable();
}

/*void InitLCD(void) {

    PORTB=0x38; EnableLCD(); delay_ms(50);
    PORTB=0x01; EnableLCD(); delay_ms(50);
    PORTB=0x0d; EnableLCD(); delay_ms(50);
    PORTB=0x06; EnableLCD(); delay_ms(50);
}

void ClearScreen(void) {

    PORTB=0x01; 
	EnableLCD();               
	delay_ms(10);
}

void GotoXY(unsigned char r, unsigned char c) {

    PORTB=0x02; EnableLCD();               
	delay_ms(10);
    for(r=r*40+c, c=0; c<r; c++) {
        PORTB= 0x14;
	    EnableLCD(); 
		delay_us(50);
    }
}*/

void PutLCD(char c) {
	write(c);
    //PORTB = c; EnableLCD2(); delay_us(50);
}
void print(char str[]){
	int i = sizeof(str);
	int j=0;
	for (j=0; j<i;j++)
		PutLCD(str[j]);
}
void PrintString(const char* s) {

    while( *s ) PutLCD(*(s++));
}

/*TECLADO*/
char key[16] = {0xEE,0xED,0XEB,0XE7,0XDE,0XDD,0XDB,0XD7,0XBE,0XBD,0XBB,0XB7,0X7E,0X7D,0X7B,0X77};
char asc[16] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x41,0x42,0x43,0x44,0x45,0x46};
unsigned char aa,bb,cc,dd,ee,ff,xx,yy,zz,boton;
char bot[9];

unsigned char GetBot(void)			//la variable de salida se define como unsigned char
{
loop:
	ee=0;
	TRISA=0x30;				/*PUERTO A:RA0,RA1,RA2 SALIDAS; RA4,RA5 ENTRADAS*/
	TRISB=0XF0;
//	RBPU=0;					//REGISTRO OPTION, BIT7. Ver función init_bolt()
							
//	PORTA=0;					/*PUERTO B RB0..RB3 SALIDAS, RB4..RB7*/
	aa=0xEF;
	PORTB=aa;
	bb=4;
	while (bb>0) 			/*4 corrimientos hacia la derecha*/
	{aa=aa/2;
	PORTB=aa;				/*ESCRIBE EN PORTB RB0..RB3*/
							/*LEE PUERTO  RB4..RB7*/
	delay_ms(5);		
	if (RB4==0||RB5==0||RB6==0||RB7==0)fin();
	if (ee==1)return (ff);		/*regresa con el valor de la tecla en ASCII*/
	bb=bb-1;}
	goto loop;

}
void fin(void){			/*tecla oprimida*/
	
	TRISB=0XF0;
	dd=PORTB;
	cc=(dd & 0XF0);		/*bits RB0..RB3 =0, conserva RB4..RB7*/
	aa=(aa & 0x0F);		/*bits RB4..RB7 =0, conserva RB0..RB3*/
	aa=(aa | cc);			/*la variable "a" contiene el código rengón columna de la tecla oprimida*/

malla:	
	dd=PORTB;			
	cc=(dd & 0XF0);			/*bits RB0..RB3 =0, conserva RB4..RB7*/
	if(cc!=0xF0)goto malla; 	/*espera que la tecla se libere*/
	TRISB=0;
	row();	
	ff=xx;			/*convierte a código ASCII*/
	ee=1;
}				
 	void row(void)
	{

	for(yy=0;yy<16;yy=yy+1)
	{if (aa==key[yy])xx=asc[yy];}	/*la variable "x" contiene el valor ASCII*/
	PORTB=xx;
	delay_ms(100);
}

void SetBot(void)
{
for(zz=0;zz<7;zz++)
{boton=GetBot();
bot[zz]=boton;
if(bot[zz]==0x46)goto qu;
else PutLCD(boton);}
qu:bot[zz]=0x00;
}

void WrtBot(void)
{
for(zz=0;zz<7;zz++)
{PutLCD(bot[zz]);
if(bot[zz+1]==0)goto ka;}
ka:zz=zz;				//expresión dummy
}

/*FUNCIONES PARA ESCRIBIR Y LEER EN LA EEPROM INTERNA*/

void writeeeprom(unsigned char addr,unsigned char byte)
{
unsigned char i=INTCONbits.GIEH;
INTCONbits.GIEH = 0; //disable interrupts
EECON1bits.EEPGD=0; //Write to EEPROM
EECON1bits.CFGS=0; //EEPROM not config bits
EECON1bits.WREN=1; //Allows write

EEADR=addr;
EEDATA=byte;
EECON2=0x55;
EECON2=0xaa;
EECON1bits.WR=1;
while(EECON1bits.WR); //Wait until written
//while(!PIR2bits.EEIF);
//PIR2bits.EEIF=0;
EECON1bits.WREN=0; //No more write
INTCONbits.GIEH = i; //restore interrupts
}

unsigned char readeeprom(unsigned char addr)
{
EECON1bits.CFGS=0; //EEPROM not config bits
EECON1bits.EEPGD=0;
EEADR=addr;
EECON1bits.RD=1;
return (unsigned int) EEDATA;
}
