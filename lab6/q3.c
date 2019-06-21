#include<LPC17xx.h>

int main()
{
	unsigned int i,x,y;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL4 &=0xFCFFFFFF;
	LPC_PINCON->PINSEL0 &=0xFF0000FF;
	LPC_GPIO0->FIODIR |=0x00000FF0;
	y = 1;
	while(1)
	{
		 x = LPC_GPIO2->FIOPIN&0x1000;
		 LPC_GPIO0->FIOPIN = y<<4;
		 if(x==0)
		 {
			 y = y<<1;
			 if(y==256)
				 y=1;
			 for(i=0;i<100000;i++);
		 }

	 }
		
 }	 
				 
			 