#include <REGX52.H>
#include "port.h"
#include "i2c.h"
#include "DS1307.h"
#include "lcd16x2.h"
#include "delay.h"
/* khai bao cac bien thoi gian */
char gio, phut, giay, ngay, thang, nam;

/*~~~~~ nguyen mau ham ~~~~~~~~*/
void bip();
void hien_thi_date();
void hien_thi_time();
void set();
void set_hour();
void set_min();
void set_sec();
void set_date();
void set_month();
void set_year();
void setup();

/*~~~~~~~~~~~~~*/
void bip()
{
	loa = 0; delay_ms(100);
	loa = 1; delay_ms(100);
}
/*~~~~~~~~~~~~~*/
void ISR_timer1() interrupt 3
{
	unsigned char x;
	TH1 = 0x3c;
	TL1 = 0xb0;
	x++;
	if(x == 20)
	{
		x = 0;
		get_time(0x00, &gio, &phut, &giay);
		get_time(0x04, &nam, &thang, &ngay);
	}
}
/*~~~~~~~~~~~~~*/
void set_hour()
{
	if(up == 0)
	{
		delay_ms(200);
		gio++;
		if(gio == 24) gio = 0;
		set_time(0x00, gio, phut, giay);
		lcd_position(1, 10);
		lcd_putc(gio/10 + 48);
		lcd_putc(gio%10 + 48); 
	}
	
	if(down == 0)
	{
		delay_ms(200);
		gio--;
		if(gio == -1) gio = 23;
		set_time(0x00, gio, phut, giay);
		lcd_position(1, 10);
		lcd_putc(gio/10 + 48);
		lcd_putc(gio%10 + 48); 
	}
}
void set_min()
{
	if(up == 0)
	{
		delay_ms(200);
		phut++;
		if(phut == 60) phut = 0;
		set_time(0x00, gio, phut, giay);
		lcd_position(1, 9);
		lcd_putc(phut/10 + 48);
		lcd_putc(phut%10 + 48); 
	}
	
	if(down == 0)
	{
		delay_ms(200);
		phut--;
		if(phut == -1) phut = 59;
		set_time(0x00, gio, phut, giay);
		lcd_position(1, 9);
		lcd_putc(phut/10 + 48);
		lcd_putc(phut%10 + 48); 
	}
}
void set_sec()
{
	if(up == 0)
	{
		delay_ms(200);
		giay++;
		if(giay == 60) giay = 0;
		set_time(0x00, gio, phut, giay);
		lcd_position(1, 9);
		lcd_putc(giay/10 + 48);
		lcd_putc(giay%10 + 48); 
	}
	
	if(down == 0)
	{
		delay_ms(200);
		giay--;
		if(giay == -1) giay = 59;
		set_time(0x00, gio, phut, giay);
		lcd_position(1, 9);
		lcd_putc(giay/10 + 48);
		lcd_putc(giay%10 + 48); 
	}
}
void set_date()
{
	if(up == 0)
	{		
		delay_ms(200);
		ngay++;
		if(ngay == 29 && thang == 2 && nam%4 == 0) ngay = 1;
		if(ngay == 30 && thang == 2 && nam%4 != 0) ngay = 1;
		if(ngay == 31 && (((thang%2 == 1) && (0 < thang < 8))||((thang%2 == 0) && (13 > thang >7)))) ngay = 1;			
		if(ngay == 32 && (((thang%2 == 0) && (2 < thang < 8))||((thang%2 == 1) && (13 > thang > 7)))) ngay = 1;	
		set_time(0x04, nam, thang, ngay);
		lcd_position(2, 10);
		lcd_putc(ngay/10 + 48);
		lcd_putc(ngay%10 + 48); 
	}
	
	if(down == 0)
	{
		delay_ms(200);
		ngay--;
		if(ngay == 0 && thang == 2 && nam%4 == 0) ngay = 28;
		if(ngay == 0 && thang == 2 && nam%4 != 0) ngay = 29;
		if(ngay == 0 && (((thang%2 == 1) && (0 < thang < 8))||((thang%2 == 0) && (13 > thang >7)))) ngay = 30;			
		if(ngay == 0 && (((thang%2 == 0) && (2 < thang < 8))||((thang%2 == 1) && (13 > thang > 7)))) ngay = 31;	
		set_time(0x04, nam, thang, ngay);
		lcd_position(2, 10);
		lcd_putc(ngay/10 + 48);
		lcd_putc(ngay%10 + 48); 
	}
}
void set_month()
{
	if(up == 0)
	{
		delay_ms(200);
		thang++;
		if(thang == 13) thang = 1;
		set_time(0x04, nam, thang, ngay);
		lcd_position(2, 11);
		lcd_putc(thang/10 + 48);
		lcd_putc(thang%10 + 48); 
	}
	
	if(down == 0)
	{
		delay_ms(200);
		thang--;
		if(thang == 0) thang = 12;
		set_time(0x04, nam, thang, ngay);
		lcd_position(2, 11);
		lcd_putc(thang/10 + 48);
		lcd_putc(thang%10 + 48); 
	}
}
void set_year()
{
	if(up == 0)
	{
		delay_ms(200);
		nam++;
		if(nam == 100) nam = 0;
		set_time(0x04, nam, thang, ngay);
		lcd_position(2, 12);
		lcd_putc(nam/10 + 48);
		lcd_putc(nam%10 + 48); 
	}
	
	if(down == 0)
	{
		delay_ms(200);
		nam--;
		if(nam == -1) nam = 99;
		set_time(0x04, nam, thang, ngay);
		lcd_position(2, 12);
		lcd_putc(nam/10 + 48);
		lcd_putc(nam%10 + 48); 
	}
}
/*~~~~~~~~~~~~~*/
void setup()
{
	bit h, m, s, d, mo, y;
	if(mode == 0)
	{
		bip();
		delay_ms(100);
		while(mode == 0);
		lcd_cmd(0x01);
		hien_thi_date();
		lcd_position(1,1);		// chuyen con tro ve hang 1 cot 1 xuat chu set hour:
    lcd_puts("set hour:", 50);	
		lcd_putc(gio/10 + 48);
		delay_ms(50);
		lcd_putc(gio%10 + 48);
		lcd_puts("         ", 50);
		h = 1;
		while(h)
		{
//			hien_thi_date();
			set_hour();		
			if(mode == 0) 
			{
				bip();
				delay_ms(100);
				while(mode == 0);
				lcd_cmd(0x01);
				hien_thi_date();
				lcd_position(1,1);
				lcd_puts("set min:", 50);	
				lcd_putc(phut/10 + 48);
				delay_ms(50);
				lcd_putc(phut%10 + 48); 
				lcd_puts("        ", 50);
				h = 0; 
				m = 1;
			}
		if(ok == 0)
		{
			bip();
			lcd_shiftleftscreen(16);
			lcd_cmd(0x01);
			while(ok == 0);
			h = 0;
		}
		}
	}
	while(m)
	{
//		hien_thi_date();
		set_min();
		if(mode == 0) 
		{
			bip();
			delay_ms(100);
			while(mode == 0);
			lcd_cmd(0x01);
			hien_thi_date();
			lcd_position(1,1);
			lcd_puts("set sec:", 50);	
			lcd_putc(giay/10 + 48);
			delay_ms(50);
			lcd_putc(giay%10 + 48); 
			m = 0; 
			s = 1;
		}
		if(ok == 0)
		{
			bip();
			lcd_shiftleftscreen(16);
			lcd_cmd(0x01);
			while(ok == 0);
			m = 0;
		}
	}
	while(s)
	{
//		hien_thi_date();
		set_sec();
		if(mode == 0) 
		{
				bip();
				delay_ms(100);
				while(mode == 0);
				lcd_cmd(0x01);
				hien_thi_time();
				lcd_position(2,1);
				lcd_puts("set date:", 50);	
				lcd_putc(ngay/10 + 48);
				delay_ms(50);
				lcd_putc(ngay%10 + 48);
				s = 0;
				d = 1;
		}
		if(ok == 0)
		{
			bip();
			lcd_shiftleftscreen(16);
			lcd_cmd(0x01);
			while(ok == 0);
			s = 0;
		}
	}
	while(d)
	{
		hien_thi_time();
		set_date();
		if(mode == 0) 
		{
				bip();
				delay_ms(100);
				while(mode == 0);
				lcd_cmd(0x01);
				hien_thi_time();
				lcd_position(2,1);
				lcd_puts("set month:", 50);	
				lcd_putc(thang/10 + 48);
				delay_ms(50);
				lcd_putc(thang%10 + 48);	
				d = 0;
				mo = 1;
		}
		if(ok == 0)
		{
			bip();
			lcd_shiftleftscreen(16);
			lcd_cmd(0x01);
			while(ok == 0);
			d = 0;
		}
	}
	while(mo)
	{
		hien_thi_time();
		set_month();
		if(mode == 0) 
		{
				bip();
				delay_ms(100);
				while(mode == 0);		
				lcd_cmd(0x01);
				hien_thi_time();			
				lcd_position(2,1);
				lcd_puts("set year:20", 50);
				lcd_putc(nam/10 + 48);
				delay_ms(50);
				lcd_putc(nam%10 + 48);	
				mo = 0;
				y = 1;
		}
		if(ok == 0)
		{
			bip();
			lcd_shiftleftscreen(16);
			lcd_cmd(0x01);
			while(ok == 0);
			mo = 0;
		}
	}
	while(y)
	{
		hien_thi_time();
		set_year();
		if(mode == 0) 
		{
			bip();
			lcd_shiftleftscreen(16);
			lcd_cmd(0x01);
			while(mode == 0);
			y = 0;
		}
		if(ok == 0)
		{
			bip();
			lcd_shiftleftscreen(16);
			lcd_cmd(0x01);
			while(ok == 0);
			y = 0;
		}
	}
}

void hien_thi_time()
{
	lcd_position(1,1);
	lcd_puts("Time: ", 1);
	lcd_putc(gio/10 + 48);
	lcd_putc(gio%10 + 48);
	lcd_putc(':');
	lcd_putc(phut/10 + 48);
	lcd_putc(phut%10 + 48);
	lcd_putc(':');
	lcd_putc(giay/10 + 48);
	lcd_putc(giay%10 + 48);
}
void hien_thi_date()
{
	lcd_position(2,1);
	lcd_puts("Date:", 1);
	lcd_putc(ngay/10 + 48);
	lcd_putc(ngay%10 + 48);
	lcd_putc('/');
	lcd_putc(thang/10 + 48);
	lcd_putc(thang%10 + 48);
	lcd_putc('/');
	lcd_puts("20", 1);
	lcd_putc(nam/10 + 48);
	lcd_putc(nam%10 + 48);
}
/*----___------*/
main()
{
	bip();
	bip();
//	control();
	lcd_init();
	TMOD = 0x10;	/* dung timer1 lay time sau moi 1s, timer0 de hien thi ra lcd */
	TH1  = 0x3c;
	TL1  = 0xb0;
	TR1  = 1;
	ET1  = 1;
	EA   = 1;
	while(1)
	{
		hien_thi_time();
		hien_thi_date();
		setup();
	}
}
