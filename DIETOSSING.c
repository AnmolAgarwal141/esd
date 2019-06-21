#include<LPC17xx.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#define RS_CTRL 1<<27
#define EN_CTRL 1<<28
#define DT_CTRL 15<<23
unsigned long int temp1=0,temp2=0,i,j,x;
int randomIndex;
unsigned char flag1=0,flag2=0;
unsigned char arr[]={"123456"};
void lcd_write(void);
void port_write(void);
void delay_lcd(unsigned int);
unsigned long int init_command[]={0x30,0x30,0x30,0x20,0x28,0x0C,0x06,0x01,0x80};

int main(void)
{
 SystemInit();
 SystemCoreClockUpdate();
 
 LPC_GPIO0->FIODIR=DT_CTRL|RS_CTRL|EN_CTRL;
 LPC_GPIO2->FIODIR&=~(1<<12);
 flag1=0;
 for(i=0;i<9;i++)
 {
    temp1=init_command[i];
	lcd_write();
	}
 flag1=1;
 
while(1)
{ 
	
	x=LPC_GPIO2->FIOPIN&(1<<12);
if(x==0)
{
 //srand ( time(NULL) );
 randomIndex = rand() % 6;
 temp1 = arr[randomIndex];
 lcd_write();
}
 }


}
 void lcd_write(void){
	flag2=(flag1==1)?0:((temp1==0x30)||(temp1==0x20))?1:0;
	temp2=temp1&0xF0;
	temp2<<=19;
	port_write();
	if(!flag2){
		temp2=temp1&0x0F;
		temp2<<=23;
		port_write();
	}
}
void port_write(void){
	LPC_GPIO0->FIOPIN=0;
	LPC_GPIO0->FIOPIN=temp2;
	if(flag1==0)
		LPC_GPIO0->FIOCLR=RS_CTRL;
	else
		LPC_GPIO0->FIOSET=RS_CTRL;
	LPC_GPIO0->FIOSET=EN_CTRL;
	delay_lcd(25);
	LPC_GPIO0->FIOCLR=EN_CTRL;
	delay_lcd(5000);
}
void delay_lcd(unsigned int r1){
	unsigned int r;
	for(r=0;r<r1;r++);
}