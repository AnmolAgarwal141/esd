#include<LPC17xx.h>
#include<stdio.h>
#define RS_CTRL 0x08000000;	//0.27
#define EN_CTRL 0x10000000;	//0.28
#define DT_CTRL 0x07800000;	//0.23-0.26

void init(void);
void clearPorts(void);
void writeCmd(void);
void writeData(void);
void disp(char *);
char to_disp[10];
float x;
int j1;
int cmd=0x0, data=0x00, flag=0;
int j,i;
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

	while(1)
	{
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
			sprintf(to_disp, "%fV", x);
			disp(&to_disp[0]);
		}

	}
}