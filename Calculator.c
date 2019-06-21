#include<LPC17xx.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#define RS_CTRL 1<<27
#define EN_CTRL 1<<28
#define DT_CTRL 15<<23
unsigned long int temp1=0,temp2=0,i,j;
int randomIndex;
unsigned char flag1=0,flag2=0,x,y,op,res,t;
unsigned char arr[13];
void lcd_write(void);
void port_write(void);
void delay_lcd(unsigned int);
char keyscan(void);
void scan(void);
unsigned long int init_command[]={0x30,0x30,0x30,0x20,0x28,0x0C,0x06,0x01,0x80};
unsigned char col,row,flag;
unsigned long i,var1,temp,temp2,temp3,twenty_count = 0x00,dig1,dig2,dig3,dig4;
unsigned char seven_seg_code[4][4]={{"0123"},{"4567"},{"89+-"},{"*/=="}};
unsigned int dig_count,num_count;

int main(void)
{
 SystemInit();
 SystemCoreClockUpdate();
 
 LPC_GPIO0->FIODIR=DT_CTRL|RS_CTRL|EN_CTRL;
  LPC_GPIO1->FIODIR=0;
  LPC_GPIO2->FIODIR=0X00003C00;
 flag1=0;
 for(i=0;i<9;i++)
 {
    temp1=init_command[i];
	lcd_write();
	}
 flag1=1;
 
	x=keyscan();
	temp1=x;
	lcd_write();
	delay_lcd(500000);
	
	flag1=0;
	temp1=init_command[7];
	lcd_write();
	
	flag1=1;
	op=keyscan();
	arr[0]=x;
	arr[1]=op;
	arr[2]='\0';
	i=0;
	while(arr[i]!='\0')
	{
		temp1=arr[i];
	lcd_write();
		i++;
	}
	delay_lcd(500000);
	 
	flag1=0;
	temp1=init_command[7];
	lcd_write();
	
	flag1=1;
	y=keyscan();
	arr[0]=x;
	arr[1]=op;
	arr[2]=y;
	arr[3]='\0';
	i=0;
	while(arr[i]!='\0')
	{
		temp1=arr[i];
	lcd_write();
		i++;
	}
	delay_lcd(500000);
	 
	flag1=0;
	temp1=init_command[7];
	lcd_write();
	
	flag1=1;
	res=keyscan();
	arr[0]=x;
	arr[1]=op;
	arr[2]=y;
	arr[3]=res;
	
	if(res=='=')
	{
		switch(op)
		{
			case '+':
				t=x+y;
			  break;
	   
			case '-':
				t=x-y;
			  break;
			default:
				break;
	  }
	}
	arr[4]=t;
	arr[5]='\0';	
	i=0;
	while(arr[i]!='\0')
	{
		temp1=arr[i];
	lcd_write();
		i++;
	}
	delay_lcd(500000);
	 
	flag1=0;
	temp1=init_command[7];
	lcd_write();
	
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
char keyscan()
{
 while(1)
  {
    for(row=0;row<4;row++)
	{
	  if(row==0)
	    temp=1<<10;
	  else if(row==1)
	    temp=1<<11;
	  else if(row==2)
	    temp=1<<12;
	  else if(row==3)
	   temp=1<<13;
	  LPC_GPIO2->FIOPIN=temp;
	  flag=0;
	  scan();
      if(flag==1)
	  {return seven_seg_code[row][col];}
	}
}
}
void scan()
{
	temp3=LPC_GPIO1->FIOPIN;
	temp3&=0x07800000;
	if(temp3!=0)
	{
		flag=1;
		if(temp3==1<<23)
			col=0;
		else if(temp3==1<<24)
			col=1;
		else if(temp3==1<<25)
			col=2;
		else if(temp3==1<<26)
			col=3;
	}
}
void delay_lcd(unsigned int r1){
	unsigned int r;
	for(r=0;r<r1;r++);
}