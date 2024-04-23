#ifndef port_h
#define port_h

sbit SDA  = P2^2;
sbit SCL  = P2^3;
sbit mode = P3^0;		
sbit up   = P3^1;
sbit down = P3^2;
sbit ok   = P3^3;
sbit loa  = P2^5;
/*----- cac phim cai dat -------*/




/* khai bao ket noi lcd */
sbit lcd_RS  = P2^6;
sbit lcd_RW  = P2^5;
sbit lcd_EN  = P2^7;

sbit lcd_DB4 = P0^4;
sbit lcd_DB5 = P0^5;
sbit lcd_DB6 = P0^6;
sbit lcd_DB7 = P0^7;


#endif
