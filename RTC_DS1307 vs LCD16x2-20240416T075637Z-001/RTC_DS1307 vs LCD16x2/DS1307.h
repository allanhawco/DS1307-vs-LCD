#ifndef DS1307_h
#define DS1307_h

/* khai bao cac ham dung voi DS1307 : doc, ghi vao DS */
unsigned char DEC_BCD(unsigned char DEC);
unsigned char BCD_DEC(unsigned char BCD);
void write_DS1307(unsigned char data_in);			/* viet 1 byte vao DS */
unsigned char read_DS1307(bit ack);									/* lay 1 byte du lieu tu DS */
void set_time(unsigned char add_reg, unsigned char hour, unsigned char min, unsigned char sec);
void get_time(unsigned char add_reg, unsigned char *hour, unsigned char *min, unsigned char *sec);
//void control();


/*-------------
----for test----
void test_write(unsigned char add_reg, unsigned char datain);
unsigned char test_read(unsigned char add_reg);
------------*/
#endif