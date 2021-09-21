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
	sw4 = 0;
	sw5 = 1;

	//global=inttochar(56);
//	hour2 = 0x09;
//	min2 = 0x08;
	hour3 = 0x09;
	min3 = 0x10;


	init_lcd();
//	DS1307_settime(0x22,0x31,0x06);		/* Set Time (hh:mm:ss) */
					 
	lcd_cmd(0x01);		
	lcd_cmd(0x80);
	lcd_data('E');lcd_data('N');lcd_data('T');lcd_data('E');lcd_data('R');lcd_data(' ');lcd_data('S');lcd_data('T');lcd_data('A');lcd_data('R');lcd_data('T');lcd_data(' ');lcd_data('T');lcd_data('I');lcd_data('M');lcd_data('E');
	delay_lcd(2000);
	for(i=0;i<2;i++)
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		if(i==0)
		{
			lcd_data('H');lcd_data('O');lcd_data('U');lcd_data('R');
		}						
		else if(i==1)
		{
			lcd_data('M');lcd_data('I');lcd_data('N');lcd_data(' ');	
		}						
		
		credit[i+1]=0;
		flg1=0;
		disp_val(0xC0,credit[i+1],4);
		while(flg1==0)
		{
			if(i==0)
			{
				if(sw1==0 && credit[i+1]<23)
				{
					credit[i+1]+=1;
					disp_val(0xC0,credit[i+1],4);				
					delay_lcd(200);
				}
			}
			else
			{
				if(sw1==0 && credit[i+1]<59)
				{
					credit[i+1]+=1;
					disp_val(0xC0,credit[i+1],4);				
					delay_lcd(200);
				}
			
			}
			if(sw2==0 && credit[i+1]>0)
			{
				credit[i+1]-=1;
				disp_val(0xC0,credit[i+1],4);
				delay_lcd(200);
			}
			if(sw3==0)
			{
				flg1=1;
				delay_lcd(200);
			}		
		}
	}
	//
	lcd_cmd(0x01);		
	lcd_cmd(0x80);
	lcd_data('E');lcd_data('N');lcd_data('T');lcd_data('E');lcd_data('R');lcd_data(' ');lcd_data('S');lcd_data('T');lcd_data('O');lcd_data('P');lcd_data(' ');lcd_data('T');lcd_data('I');lcd_data('M');lcd_data('E');
	delay_lcd(2000);
	for(i=0;i<2;i++)
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		if(i==0)
		{
			lcd_data('H');lcd_data('O');lcd_data('U');lcd_data('R');
		}						
		else if(i==1)
		{
			lcd_data('M');lcd_data('I');lcd_data('N');lcd_data(' ');	
		}						
		
		credit2[i+1]=0;
		flg1=0;
		disp_val(0xC0,credit2[i+1],4);
		while(flg1==0)
		{
			if(i==0)
			{
				if(sw1==0 && credit2[i+1]<23)
				{
					credit2[i+1]+=1;
					disp_val(0xC0,credit2[i+1],4);				
					delay_lcd(200);
				}
			}
			else
			{
				if(sw1==0 && credit2[i+1]<59)
				{
					credit2[i+1]+=1;
					disp_val(0xC0,credit2[i+1],4);				
					delay_lcd(200);
				}
			
			}
			if(sw2==0 && credit2[i+1]>0)
			{
				credit2[i+1]-=1;
				disp_val(0xC0,credit2[i+1],4);
				delay_lcd(200);
			}
			if(sw3==0)
			{
				flg1=1;
				delay_lcd(200);
			}		
		}
	}
	//
	hour2 = inttochar(credit[1]);
	min2  = inttochar(credit[2]);
	hour3 = inttochar(credit2[1]);
	min3  = inttochar(credit2[2]);

	lcd_cmd(0x01);
	while(1)
	{	 	
		sec   = DS1307_get(SEC);	
		min   = DS1307_get(MIN);	
		hour  = DS1307_get(HOUR);
		display_time(hour,min,sec);
		/*if(global==0)
		{
			if((min2==min) &&(hour2==hour))
			{	
				lcd_cmd(0xC0);						
				lcd_data('S');lcd_data('Y');lcd_data('S');lcd_data('T');lcd_data('E');lcd_data('M');lcd_data(' ');lcd_data('O');lcd_data('N');
				delay_lcd(2000);
				lcd_cmd(0xC0);						
				lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');
				global=1;
			}
		}
	
		if(global==1)
		{				 
			if(IR==1)
			{
				lcd_cmd(0xC0);
				lcd_data('D');lcd_data('E');lcd_data('T');lcd_data('E');lcd_data('C');lcd_data('T');lcd_data('E');lcd_data('D');lcd_data(' ');
				sw4=1;
				delay_lcd(500);
				sw4=0;
				delay_lcd(500);
				sw5=0;
				delay_lcd(500);
				sw5=1;
				lcd_cmd(0xC0);						
				delay_lcd(500);
				lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');			
			}
			
		}
		if(global==1)
		{
			if((min3==min) &&(hour3==hour))
			{	
				lcd_cmd(0xC0);						
				lcd_data('S');lcd_data('Y');lcd_data('S');lcd_data('T');lcd_data('E');lcd_data('M');lcd_data(' ');lcd_data('O');lcd_data('F');lcd_data('F');
				delay_lcd(2000);
				lcd_cmd(0xC0);						
				lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data(' ');
				global=0;
			}
		} */
				
	}					   	
	return 0;
}
