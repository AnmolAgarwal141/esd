#include<LPC17xx.h>
#include<stdio.h>
#define RS_CTRL 0x08000000;	//0.27
#define EN_CTRL 0x10000000;	//0.28
#define DT_CTRL 0x07800000;	//0.23-0.26

void init(void);
void init1(void);

void clearPorts(void);
void writeCmd(void);
void writeData(void);
void disp(char *);
char to_disp[10];
float x,temp3=0,temp4;
int j1;
int cmd=0x0, data=0x00, flag=0;
int j,i;
float scan()
{
	while(1){
	flag=0;
		data = 0x80;		//move to first line, first column
		writeData();
		for(j1=0;j1<30000;j1++);
		LPC_ADC->ADCR = 0x01200020;
		for(j1=0;j1<2000;j1++);
		if(LPC_ADC->ADGDR & 0x1<<31)
		{
			x = (LPC_ADC->ADGDR & 0xFFF0)>>4;
			x = x*0.0008;
			x= x*9.5/3.3+90;
			sprintf(to_disp, "%fV", x);
			disp(&to_disp[0]);
			if(x<=93.0)
			{
			temp3=x-92.7;
					break;
			}
			else if(x<=93.8)
			{
			 temp3=x-93.5;
	      break;
			 }
			 else if(x<=98.6)
			 { temp3=x-98.3;
         break;
			 }
		}
	}
	return temp3;
}

void init1(void){
		LPC_PINCON->PINSEL3&= ~(0x0000C000);
		LPC_PINCON->PINSEL3 |= 0x00008000;
	  //LPC_PINCON->PINSEL3 = 2<<14;
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

void init()
{
	LPC_PINCON->PINSEL1 = 0xFC003FFF;
	LPC_GPIO0->FIODIRH = 0x1F80;
	clearPorts();
	flag=0;
	for(j=0;j<3200;j++);

	for(i=0;i<3;i++)		//wake up
	{
		cmd = 0x3<<23;
		writeCmd();
		for(j=0;j<30000;j++);
	}
	cmd = 0x2<<23;		//return home
	writeCmd();
	for(j=0;j<30000;j++);

	data = 0x28;		//inform that there are 2 lines, default font
	writeData();
	for(j=0;j<30000;j++);

	data = 0x01;		//clear display
	writeData();
	for(j=0;j<10000;j++);

	data = 0x06;		//increment cursor after writing, don't shift data
	writeData();
	for(j=0;j<800;j++);

	data = 0x80;		//move to first line, first column
	writeData();
	for(j=0;j<800;j++);

	data = 0x0F;		//switch on LCD, show cursor and blink
	writeData();
	for(j=0;j<800;j++);
}

void clearPorts()
{
	LPC_GPIO0->FIOCLRH = 0x1F80;
}

void writeCmd()
{
	clearPorts();
	LPC_GPIO0->FIOPIN = cmd;
	if(flag==0)
	{
		LPC_GPIO0->FIOCLR = RS_CTRL;
	}
	else if(flag==1)
	{
		LPC_GPIO0->FIOSET = RS_CTRL;
	}
	LPC_GPIO0->FIOSET = EN_CTRL;
	for(j=0;j<50;j++);
	LPC_GPIO0->FIOCLR = EN_CTRL;
}

void writeData()
{
	cmd = (data & 0xF0)<<19;
	writeCmd();
	cmd = (data & 0x0F)<<23;
	writeCmd();
	for(j=0;j<1000;j++);
}

void disp(char *to_disp)
{
	i = 0;
	while(to_disp[i]!='\0')
	{
		data = to_disp[i];
		flag=1;
		writeData();
		i++;
	}
}
int main(void)
{
	LPC_SC->PCONP &= (0x1<<12)|(0x1<<15);
	LPC_PINCON->PINSEL3 = 0xC0000000;	//P1.31 for channel 5
	init();
  init1();
	while(1)
	{
		for (i=0;i<100;i++);

	}
}