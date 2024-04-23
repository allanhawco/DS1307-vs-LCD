#include <REGX52.H>				/* cho phep giao tiep voi cac port cua VDK */
#include "i2c.h"
#include "port.h"
#include "delay.h"

/* dinh nghia cac ham trong i2c.h */
/*-----------*/
void delay(int time)
{
	while(time--);
}
/*-----------*/
void i2c_clock()
{
	delay(1);
	SCL = 1;
	delay(1);
	SCL = 0;
}
/*----------------------*/
void i2c_ack()
{
	SDA = 0;
	i2c_clock();
	SDA = 1;			/* dua ve trang thai free */
}
/*----------------------*/
void i2c_nack()
{
	SDA = 1;
	i2c_clock();
	SDA = 1;			/* dua ve trang thai free */
}
/*------start condition-----*/
/*--------------------
SDA: ______
					 \_____________
SCL: __________
							 \_________
----------------------*/
void i2c_start()
{
	SDA = 1;
	SCL = 1;
	delay(1);
	SDA = 0;
	delay(1);
	SCL = 0;
}
/*------stop condition-----*/
/*--------------------
SDA:  __      ______
				\____/
SCL:     __________
			__/				 
----------------------*/
void i2c_stop()
{
	SDA = 1;
	SCL = 0;
	delay(1);
	SDA = 0;
	SCL = 1;
	delay(2);
	SDA = 1;
	SCL = 1;
}
/*-----trich mau du lieu tren duong SDA------*/
/*------____  ____  ____       ____        ____
SDA:   / 1  \/ 2  \/ 3  \...../ 8  \      /      
       \____/\____/\____/     \____/\____/
SCL:      _     _     _          _     _
			 __/ \___/ \___/ \_......_/ \___/ \_....
----------------------*/
void i2c_write(unsigned char datain)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		SDA = datain & 0x80;
		i2c_clock();
		datain = datain << 1;
	}
	i2c_clock();		/* cho bit ack tu DS1307 */
	SDA = 1;				/* keo SDA len 1 sau moi lan viet */
}
/*-  __  ____  ____  ____       ____        ____
SDA:   \/ 1  \/ 2  \/ 3  \...../ 8  \      /      
        \____/\____/\____/     \____/\____/
SCL:       _     _     _          _     _
		 _____/ \___/ \___/ \_......_/ \___/ \_....
----------------------*/
unsigned char i2c_read(bit ack)
{
	unsigned char dataout = 0x00, i;
//	SDA = 1;                   
	for(i = 0; i < 8; i++)
	{

		delay(1); 
		dataout = dataout << 1;
		dataout = dataout | SDA;		/* lay bit dau tien */
		i2c_clock();
	}
	if(ack == 0) i2c_ack();
	else i2c_nack();
	SDA = 1;
	return dataout;
}
