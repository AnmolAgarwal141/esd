#include<LPC17xx.h>
#include<stdio.h>
float in_vtg4,in_vtg5,res;
char vtg4[7],dval4[7],vtg5[7],dval5[7],resa[7],m[1]={"-"},e[1]={"="};
void ADC_IRQHandler(void);
#define RS_CTRL 1<<27
#define EN_CTRL 1<<28
#define DT_CTRL 15<<23
unsigned long int temp1=0,temp2=0,i,j,x;
unsigned char flag1=0,flag2=0;
unsigned char arr[30];
void lcd_write(void);
void port_write(void);
void delay_lcd(unsigned int);
unsigned long int init_command[]={0x30,0x30,0x30,0x20,0x28,0x0C,0x06,0x01,0x80};


int main(void)
{
	SystemInit();
  SystemCoreClockUpdate();
 
  LPC_GPIO0->FIODIR=DT_CTRL|RS_CTRL|EN_CTRL;
	LPC_PINCON->PINSEL3=(3<<28)|(3<<30);
	LPC_ADC->ADCR=(1<<4)|(1<<5)|(1<<16)|(1<<21);
	LPC_ADC->ADINTEN=(1<<4)|(1<<25);
	NVIC_EnableIRQ(ADC_IRQn);
	flag1=0;
 for(i=0;i<9;i++)
 {
    temp1=init_command[i];
	lcd_write();
	}
 flag1=1;
	while(1);/*{
		
		//lcd
		//strcat(arr,vtg5);
		//strcat(arr,m);
		//strcat(arr,vtg4);
		//strcat(arr,e);
		//strcat(arr,resa);
		//i=0;
		while(arr[i]!='\0')
		{
			temp1=arr[i];
		 lcd_write();
			i++;
		}
		for(i=0;i<7;i++)
		vtg5[i]=vtg4[i]=resa[i]=0;
		for(i=0;i!='\0';i++)
		arr[i]=0;
		delay_lcd(500000);
	
	flag1=0;
	temp1=init_command[7];
	lcd_write();
	
	flag1=1;}*/
	
}

void ADC_IRQHandler(void)
{
	int channel, temp, result4,result5;
	channel=(LPC_ADC->ADGDR>>24)&0x07;
	if(channel==4)
	{
		temp=LPC_ADC->ADDR4;
		temp=temp>>4;
		temp&=0xFFF;
		in_vtg4=(float)temp*3.3/4096;
		sprintf(vtg4,"%fV",in_vtg4);
		sprintf(dval4,"%x",temp);
		
		//lcd
		i = 0;
	while(vtg4[i]!='\0')
	{
		temp1 = vtg4[i];
		lcd_write();
		i++;
	}
	for(i=0;i<7;i++)
		vtg4[i]=dval4[i]=resa[i]=0;
	}
	if(channel==5)
	{
		temp=LPC_ADC->ADDR5;
		temp=temp>>4;
		temp&=0xFFF;
		in_vtg5=(float)temp*3.3/4096;
		res=in_vtg5-in_vtg4;
		sprintf(vtg5,"%fv",in_vtg5);
		sprintf(resa,"%fv",res);
		sprintf(dval5,"%x",temp);
    while(vtg5[i]!='\0')
	{
		temp1 = vtg5[i];
		lcd_write();
		i++;
	}
	for(i=0;i<7;i++)
		vtg5[i]=dval5[i]=resa[i]=0;
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