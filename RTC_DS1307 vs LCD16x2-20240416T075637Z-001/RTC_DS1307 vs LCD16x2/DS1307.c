#include <REGX52.H>
#include "i2c.h"
#include "DS1307.h"

/* dinh nghia cac ham trong DS1307.h */
/*-- chuyen doi bcd-dec, dec-bcd -----*/
unsigned char DEC_BCD(unsigned char DEC)
{
	unsigned char temp = DEC;
	return (((DEC/10)*16) + (temp%10));
}
/*---------------*/
unsigned char BCD_DEC(unsigned char BCD)
{
	unsigned char temp = BCD;
	return ((BCD/16)*10 + temp%16);
}
/*-----Qua trinh ghi 1 byte du lieu-------------*/
void write_DS1307(unsigned char data_in)
{
	unsigned char temp = DEC_BCD(data_in);
	i2c_write(temp);												/* ket qua viet vao la 1 so BCD */
}
/*-----Qua trinh lay 1 byte du lieu-------------*/
unsigned char read_DS1307(bit ack)
{
	unsigned char data_out, temp;
	data_out = i2c_read(ack);
	temp  = BCD_DEC(data_out);
	return temp;													/* ket qua lay ra la 1 so DEC */
}
/*-- cac ham cai thoi gian va lay thoi gian ra --*/
/*-----Qua trinh ghi 3 byte du lieu : 3 so DEC->BCD-------------*/
void set_time(unsigned char add_reg, unsigned char hour, unsigned char min, unsigned char sec)
{
	i2c_start();
	i2c_write(0xD0);		/* dia chi DS va bit cho phep viet vao DS 0x68<<1 | 0*/
	i2c_write(add_reg);		/* dia chi thanh ghi dau tien */
	write_DS1307(sec);
	write_DS1307(min);
	write_DS1307(hour);
	i2c_stop();
}
/*-----Qua trinh lay 3 byte du lieu : 3 so BCD->DEC-------------*/
void get_time(unsigned char add_reg, unsigned char *hour, unsigned char *min, unsigned char *sec)	
{
	i2c_start();
	i2c_write(0xD0);
	i2c_write(add_reg);		/* lay du lieu bat dau tu thanh ghi co dia cho add_reg */
//	i2c_stop();
	
	i2c_start();
	i2c_write(0xD1);		/* dia chi DS va bit cho phep doc tu DS */
	*sec  = read_DS1307(0);	
	*min  = read_DS1307(0);			
	*hour = read_DS1307(1);	 
	
	i2c_stop();
}
/*---------------*/
void control()
{
	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x07);
	i2c_write(0x10);
	i2c_write(0x93);
	i2c_stop();
}

/*for test*/

void test_write(unsigned char add_reg, unsigned char datain)
{
	datain = DEC_BCD(datain);
	i2c_start();
	i2c_write(0xD0);
	i2c_write(add_reg);
	i2c_write(datain);
	i2c_stop();
}

unsigned char test_read(unsigned char add_reg)
{
	unsigned char dataout;
	i2c_start();
	i2c_write(0xD0);
	i2c_write(add_reg);
	i2c_start();
	i2c_write(0xD1);
	dataout = i2c_read(1);
	i2c_stop();
	dataout = BCD_DEC(dataout);
	return dataout;
}















