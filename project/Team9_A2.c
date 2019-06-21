#include <LPC17xx.h>
#include<stdio.h>
#define RS_CTRL 1<<27
#define EN_CTRL 1<<28
#define DT_CTRL 15<<23

int temp1=0,temp2=0,i,j,adc_temp;
unsigned char flag1=0,flag2=0;
float in_vtg,result,temp4,temp3;
char res[10];
void lcd_write(void);
void init(void);
void port_write(void);
void delay_lcd(unsigned int);
void PWM1_IRQHandler(void);
void display(void);
float scan(void);
unsigned long int init_command[]={0x30,0x30,0x30,0x20,0x28,0x0C,0x06,0x01,0x80};
void init(void){
		LPC_PINCON->PINSEL3&= ~(0x0000C000);
		LPC_PINCON->PINSEL3 |= 0x00008000;
		LPC_PWM1->PCR=0x1000;
		LPC_PWM1->MCR=0x3;
		LPC_PWM1->MR0=30000;
		LPC_PWM1->MR4=40000;
		LPC_PWM1->LER=0xFF;
		LPC_PWM1->TCR=0x02;
		LPC_PWM1->TCR=0x09;
		NVIC_EnableIRQ(PWM1_IRQn);
		return;
}

void PWM1_IRQHandler(void){
	LPC_PWM1->IR = 0xFF;
	temp4=scan();
	if(temp4==-0.2||temp4==0.2)
	   LPC_PWM1->MR4=3000;
	else if (temp4==-0.1||temp4==0.1){
			LPC_PWM1->MR4=15000;
	}
	else if (temp4==0){
			LPC_PWM1->MR4=30000;
	}
	LPC_PWM1->LER=0xFF;
}

int main(void){
		SystemInit();
		SystemCoreClockUpdate();
        LPC_GPIO0->FIODIR=DT_CTRL|RS_CTRL|EN_CTRL;
	    LPC_PINCON->PINSEL3=(3<<28);
	
	    flag1=0;
        for(i=0;i<9;i++)
        {
          temp1=init_command[i];
	      lcd_write();
	    }
        flag1=1;
		init(); 
}
float scan()
{
		
	while(1)
	{
		flag1=0;
		temp1 = 0x80;		//move to first line, first column
		lcd_write();
		flag1=1;
		for(i=0;i<30000;i++);
		LPC_ADC->ADCR = (1<<4)|(1<<21)|(1<<24);
		for(i=0;i<2000;i++);
		if(LPC_ADC->ADDR4 & 1<<31)
		{
		
			adc_temp=LPC_ADC->ADDR4;
			adc_temp >>=4;
			adc_temp&=0xFFF;
			in_vtg=(float)(adc_temp*3.3/4096);
			result=(in_vtg*(9.5/3.3))+90;
			sprintf(res,"%3.2fv",result);
			display();
			if(result<=93.0)
			{
			temp3=result-92.7;
			break;			
			}
			else if(result<=93.8)
			{
			 temp3=result-93.5;
			 break;
			 }
			 else if(result<=98.6)
			 { temp3=result-98.3;
			 break;
			 }
		}
	}
		 return temp3;

}
void display()
{
 i=0;
 while(res[i]!='\0')
 {
 temp1=res[i];
 lcd_write();
 i++;
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
	
	
	/*
	i=0;
			while(res[i]!='\0')
			{res[i]=0;
			i++;*/