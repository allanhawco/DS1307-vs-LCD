#ifndef lcd16x2_h
#define lcd16x2_h



/*~~~~~~~~*/
void lcd_init();									/* initialize lcd */
void _4bit_high(unsigned char);
void _4bit_low(unsigned char);
void lcd_cmd(unsigned char);			/* write command */
void lcd_data(unsigned char);			/* write data */
void lcd_putc(unsigned char);
void lcd_puts(unsigned char *, int);
void lcd_position(unsigned char, unsigned char);
void lcd_shiftleftAC(unsigned char);
void lcd_shiftleftscreen(unsigned char);
//void hien_thi(unsigned char, unsigned char, unsigned char);
/*~~~~~~~~*/

#endif