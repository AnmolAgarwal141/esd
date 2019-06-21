#include<LPC17xx.h>
#include<stdio.h>
float in_vtg4,in_vtg5,res;
char vtg4[7],dval4[7],vtg5[7],dval5[7],resa[7],m[1]={"-"},e[1]={"="};
void ADC_IRQHandler(void);
#define RS_CTRL 1<<27
#define EN_CTRL 1<<28
#define DT_CTRL 15<<23
unsigned long int temp1=0,temp2=0,i,j;
unsigned char flag1=0,flag2=0;
unsigned char arr[30];
void lcd_write(void);
void port_write(void);
void delay_lcd(unsigned int);
unsigned long int init_command[]={0x30,0x30,0x30,0x20,0x28,0x0C,0x06,0x01,0x80};
int x,y;
char to_disp[10],to_disp1[10];
int main(void)
{
	SystemInit();
  SystemCoreClockUpdate();
 
  LPC_GPIO0->FIODIR=DT_CTRL|RS_CTRL|EN_CTRL;
	LPC_PINCON->PINSEL3=(3<<28)|(3<<30);
	
	flag1=0;
 for(i=0;i<9;i++)
 {
    temp1=init_command[i];
	lcd_write();
	}
 flag1=1;
	while(1){
		
	LPC_ADC->ADCR=(1<<4)|(1<<5)|(1<<24)|(1<<21);
	for(i=0;i<2000;i++);
		if(LPC_ADC->ADDR4 & 0x1<<31)
		{
			x = (LPC_ADC->ADDR4 & 0xFFF0)>>4;
			x = x*0.0008;
			sprintf(to_disp, "%fV", x);
			i = 0;
	    while(to_disp[i]!='\0')
	    {
	    	temp1 = to_disp[i];
		    flag1=1;
		    lcd_write();
		    i++;
    	}
		}
	if(LPC_ADC->ADDR5 & 0x1<<31)
		{
			y = (LPC_ADC->ADDR5 & 0xFFF0)>>4;
		  y = y*0.0008;
			sprintf(to_disp1, "%fV", y);
			i = 0;
	    while(to_disp1[i]!='\0')
	    {
	    	temp1 = to_disp1[i];
		    flag1=1;
		    lcd_write();
		    i++;
    	}
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