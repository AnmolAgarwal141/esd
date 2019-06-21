#include<LPC17xx.h>

int main()
{
	unsigned int i,x =0x0;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &=0xFF0000FF;
	LPC_GPIO0->FIODIR |=0x00000FF0;
	while(1)
	{
			LPC_GPIO0->FIOPIN = x<<4;
			x++;
			for(i=0;i<1000000;i++);
	
		if(x == 0xFF)
			x = 0;
  }
}