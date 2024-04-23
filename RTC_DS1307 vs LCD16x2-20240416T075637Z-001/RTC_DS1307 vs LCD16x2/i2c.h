#ifndef i2c_h
#define i2c_h

void delay(int time);
void i2c_clock();												/* trich mau du lieu va cho phep thay doi du lieu tren duong SDA */
void i2c_start();												/* bat dau giao tiep i2c */
void i2c_stop();												/* ket thuc giao tiep i2c */
void i2c_write(unsigned char datain);		/* viet du lieu vao slave */
unsigned char i2c_read(bit ack);				/* lay du lieu tra ve tu slave */
void i2c_ack();													/* gui tin hieu ack xac nhan muon truyen nhan tiep */
void i2c_nack();												/* gui tin hieu nack xac nhan khong muon truyen nhan tiep */

#endif