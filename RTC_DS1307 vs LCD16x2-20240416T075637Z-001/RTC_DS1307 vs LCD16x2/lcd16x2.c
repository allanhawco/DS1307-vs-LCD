/* giao tiep 4 bit */

#include <REGX52.H>
#include <string.h>
#include "lcd16x2.h"
#include "port.h"
#include "delay.h"


#define left 0x18
#define right 0x1c

/*~~~~~~~~*/

/*~~~~~~~~*/
void lcd_init()
{
	lcd_cmd(0x38);
	delay_ms(5);
	lcd_cmd(0x38);
	delay_ms(1);
	lcd_cmd(0x38);
	
	/* funtion set 4bit */
	_4bit_high(0x20);
	lcd_EN = 0;
	lcd_EN = 1;
	delay_ms(2);
	
	lcd_cmd(0x28);		/* comunicate 4 bit */
	lcd_cmd(0x01);		/* clear all */
	lcd_cmd(0x0C);		/* turn on lcd and turn off poitnter */

}
/*~~~~~~~~*/
void _4bit_high(unsigned char high)
{
	lcd_DB7 = high & 0x80;
	lcd_DB6 = high & 0x40;
	lcd_DB5 = high & 0x20;
	lcd_DB4 = high & 0x10;
}
/*~~~~~~~~*/
void _4bit_low(unsigned char low)
{
	lcd_DB7 = low & 0x08;
	lcd_DB6 = low & 0x04;
	lcd_DB5 = low & 0x02;
	lcd_DB4 = low & 0x01;
}
/*~~~~~~~~*/
void lcd_cmd(unsigned char cmd)
{
	lcd_RW = 0;  /* write */
	lcd_RS = 0;  /* thao tac voi lenh */

	/* gui 4 bit cao */
	_4bit_high(cmd);
	lcd_EN = 0;
	lcd_EN = 1;
	delay_ms(2);
	/* gui 4 bit thap */
	_4bit_low(cmd);
	lcd_EN = 0;
	lcd_EN = 1;
	delay_ms(2);


}
/*~~~~~~~~*/
void lcd_data(unsigned char dat)
{
	lcd_RW = 0;  /* ghi */
	lcd_RS = 1;  /* thao tac voi du lieu */
	/* gui 4 bit cao */
	_4bit_high(dat);
	lcd_EN = 0;
	lcd_EN = 1;
	delay_ms(1);
	/* gui 4 bit thap */
	_4bit_low(dat);
	lcd_EN = 0;
	lcd_EN = 1;
	delay_ms(1);
}
/*~~~~~~~~*/
void lcd_putc(unsigned char c)
{
	lcd_data(c);
}
/*~~~~~~~~*/
void lcd_puts(unsigned char *str, int v)
{
	unsigned char length = strlen(str), i;
	for(i = 0; i < length; i++)
	{
		lcd_data(*(str+i));
		delay_ms(v);
	}
}
/*~~~~~~~~*/
void lcd_position(unsigned char row, unsigned char column)
{
	if(row == 1)	lcd_cmd(0x80|(column - 1));
	if(row == 2)  lcd_cmd(0xC0|(column - 1));
}
/*~~~~~~~~*/
void lcd_shiftleftAC(unsigned char x)
{
	unsigned char i;
	for(i = 0; i < x; i++)
	{
		lcd_cmd(0x10); // dich con tro AC sang trai i don vi
	}
}
/*~~~~~~~~*/
void lcd_shiftleftscreen(unsigned char i)
{
	unsigned char x;
  for(x = 0; x < i; x++)
	{
		lcd_cmd(left);
		delay_ms(100);
	}
}
//void hien_thi(unsigned char gio, unsigned char phut , unsigned char giay)
//{
//	unsigned char c_gio, dv_gio, c_phut, dv_phut, c_giay, dv_giay;
//	c_gio = gio / 10 + 48;
//	dv_gio = gio%10 + 48;
//	c_phut = phut/10 + 48;
//	dv_phut = phut%10 + 48;
//	c_giay = giay/10 + 48;
//	dv_giay = giay%10 + 48;
//	lcd_position(1, 1);
//	lcd_puts("time:");
//	lcd_putc(c_gio);
//	lcd_putc(dv_gio);
//	lcd_putc(':');
//	lcd_putc(c_phut);
//	lcd_putc(dv_phut);
//	lcd_putc(':');
//	lcd_putc(c_giay);
//	lcd_putc(dv_giay);
//}
///*~~~~~~~~*/
//main()
//{
//	lcd_init();
////	lcd_position(1, 5);
////	lcd_putc(48);

//	lcd_position(2, 3);
//	lcd_puts("chung");
//	while(1)
//	{
//		for(giay = 0; giay < 61; giay++)
//		{
//			if(giay == 60) { phut++; giay = 0; }
//			if(phut == 60) gio++;
//			hien_thi(gio, phut, giay);
//			delay_ms(500);
//		}
//	}
//}