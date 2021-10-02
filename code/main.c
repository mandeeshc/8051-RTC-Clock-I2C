#include <REGX51.H>
#include "ds1307.h"
#define LCD P0	
//****************************************
sbit RS = P1^0;	     
sbit EN = P1^1;

sbit sw1 = P1^4;
sbit sw2 = P1^5;
sbit sw3 = P1^6;

sbit sw4 = P3^0;
sbit sw5 = P3^1;

//sbit IR = P1^7;

char arr_t[10];
int credit[4];
int credit2[4];
int global=0;
//****************************************
void init_lcd(void);
void lcd_data(char);
void lcd_cmd(char);
//****************************************
void delay_lcd(int DD)
{
	int i,j;
	for(i=1;i<=DD;i++)
	{
		for(j=1;j<=50;j++);
	}
}
//****************************************
void init_LCD()
{
	RS=0;
	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x0F);
	lcd_cmd(0x0C);
	lcd_cmd(0x80);
	lcd_data('O');
	lcd_data('K');
	delay_lcd(1000);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
}
//****************************************
void lcd_data(char dta)
{
	RS=1;
	LCD = dta;
	EN=1;
	delay_lcd(6);
	EN=0;
}

void lcd_string(char *dat)
{
	while(*dat)
	{
		lcd_data(*dat++);
	}
}
//****************************************
void lcd_cmd(char cmmd)
{
	RS=0;
	LCD = cmmd;
	EN=1;
	delay_lcd(6);
	EN=0;
}	
//****************************************
void clear_arr_t()
{
	int i;
	for(i=0;i<10;i++)
	{
	 	arr_t[i]=' ';
	}	
}
//****************************************
void disp_val(char add, int value, int space)
{	
//	char arr_t[10];
	int c1=0,i;
	int v1=value;	
	lcd_cmd(add);
	for(i=0;i<space;i++)
	{
		lcd_data(' ');
	}
	if(v1!=0)
	{	
		clear_arr_t();
		while(v1!=0)	
		{			
			arr_t[c1] = (v1%10)+48;
			v1 = v1/10;
			c1++; 
		}  
		lcd_cmd(add);
		for(i=c1-1;i>=0;i--)
		{
			lcd_data(arr_t[i]);
		}
	}
	else
	{
		lcd_cmd(add);
		lcd_data('0');		
	}
}
//****************************************
void display_time(int hour,int min,int sec)
{
		unsigned char buf;
		lcd_cmd(0x80);
		lcd_data('T');lcd_data('I');lcd_data('M');lcd_data('E');lcd_data(' ');lcd_data(':');lcd_data(' ');

		buf = hour & 0xF0;
		buf = (buf>>4);
		buf = buf + 48;
		lcd_data(buf);

		buf = hour & 0x0F;
		buf = buf + 48;  
		lcd_data(buf);	   

		lcd_data(':');
		
		buf = min & 0xF0;
		buf = (buf>>4);
		buf = buf + 48;
		lcd_data(buf);

		buf = min & 0x0F;
		buf = buf + 48;  
		lcd_data(buf);	   

		lcd_data(':');

		buf = sec & 0xF0;
		buf = (buf>>4);
		buf = buf + 48;  
		lcd_data(buf);

		buf = sec & 0x0F;
		buf = buf + 48;  
		lcd_data(buf);

}
//****************************************
char inttochar(int val)
{
	char ret;
	int tmp,tmp1,tmp2;

	tmp = val;
	tmp1 = (tmp%10);
	tmp=tmp/10;
	tmp2 = (tmp%10);
	tmp2 = tmp2<<4;
	ret = tmp1|tmp2;
	return ret;
}
//****************************************
int main()
{		
	int i,flg1;
	unsigned char sec, min, hour;
	unsigned char min2,hour2,min3,hour3;
	//sw4 = 0;
	//sw5 = 1;
	hour3 = 0x09;
	min3 = 0x10;


	init_lcd();
  //DS1307_settime(0x17,0x48,0x06);		/* Set Time (hh:mm:ss)  Uncomment & Program time, then comment and program .code*/
	lcd_cmd(0x01);
	while(1)
	{	 	
		sec   = DS1307_get(SEC);	
		min   = DS1307_get(MIN);	
		hour  = DS1307_get(HOUR);
		display_time(hour,min,sec);
	}					   	
	return 0;
}
