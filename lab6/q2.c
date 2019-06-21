#include<LPC17xx.h>

int main()
{
	unsigned int i,x,y;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL4 &=0xFCFFFFFF;
	LPC_PINCON->PINSEL0 &=0xFF0000FF;
	LPC_GPIO0->FIODIR |=0x00000FF0;
	y = 0;
	while(1)
	{
		 x = LPC_GPIO2->FIOPIN&0x1000;
		 LPC_GPIO0->FIOPIN = y<<4;
		 if(x == 0)
		 {
			 y--;
			 if(y==-1)
					y=0xFF;
			 for(i=0;i<100000;i++);
		 }
		 else
		 {
			 y++;
			 if(y==0xFF)
				 y=0;
			 for(i=0;i<100000;i++);
		 }

	 }
		
 }	 
				 
			 