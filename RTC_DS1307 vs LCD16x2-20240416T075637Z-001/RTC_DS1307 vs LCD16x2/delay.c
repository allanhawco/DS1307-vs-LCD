#include "delay.h"

void delay_ms(int time)
{
	int x, y;
	for(x = 0; x < time; x++)
	{
		for(y = 0; y < 125; y++);
	}
}
