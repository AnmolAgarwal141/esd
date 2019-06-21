#include<lpc17xx.h>

#define FIRST_SEG 0<<23
#define SECOND_SEG 1<<23
#define THIRD_SEG 2<<23
#define FOURTH_SEG 3<<23
unsigned char Code_arr[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
int dig1=0,dig2=0,dig3=0,dig4=0;
unsigned int digit_ct =0,flag=0;
unsigned long int temp1,temp2;

void Display(void);
void Delay(void);
void Digit_check(void);

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	LPC_GPIO0->FIODIR = 0x00000FF0;
	LPC_GPIO1->FIODIR = 0x07800000;
	while(1)
	{
		if(digit_ct == 4) digit_ct = 0;
		if(flag) 
		{
			Digit_check();
			flag = 0;
		}
		Display();
		digit_ct +=1;
		Delay();
	}
	return 0;
}	

void Display(void)
{
	if(digit_ct == 0){
		temp1 = dig1;
		LPC_GPIO1->FIOPIN = FIRST_SEG;
	}
	else if(digit_ct == 1){
		temp1 = dig2;
		LPC_GPIO1->FIOPIN = SECOND_SEG;
	}
	else if(digit_ct == 2){
		temp1 = dig3;
		LPC_GPIO1->FIOPIN = THIRD_SEG;
	}
	else if(digit_ct == 3){
		temp1 = dig4;
		LPC_GPIO1->FIOPIN = FOURTH_SEG;
	}
	temp1 &= 0x0F;
	temp2 = Code_arr[temp1];
	LPC_GPIO0->FIOPIN = temp2<<4;
	if(digit_ct == 2)
	{
		LPC_GPIO0->FIOSET = 1<<11;
	}
	Delay();
}	

void Digit_check(void)
{
	dig1 += 1;
	if(dig1 == 0x0A)
	{
		dig1 = 0;
		dig2 += 1;
		if(dig2 == 0x06)
		{
			dig3 += 1;
			dig2 = 0;
			if(dig3 == 0x0A & dig4 == 0)
			{
				dig3 = 0;
				dig4 += 1;
			}
			if(dig3 == 0x02 & dig4 == 1){
				dig4 += 1;
				dig3 = 0;
				if(dig4 == 0x02)
				{
					dig4 = 0;
				}
			}
		}
	}
}

void Delay(void)
{
	int i;
	for(i=0;i<3900;i++);
	flag = 1;
}
