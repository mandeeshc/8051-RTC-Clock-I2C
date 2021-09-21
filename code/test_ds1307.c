#include <p89v51rd2.h>  		
#include "ds1307.h"		
#include "lcd.h"	

void PowerOn()
{
    unsigned char inner, outer;

    for (outer = 0x00; outer < 0x10; outer++) 
    {
        for (inner = 0x00; inner < 0xFF; inner++);
    }
    
    LCD_init();
    
    for (inner = 0; inner < 10; inner++) 
    	LCD_delay(2);
}

void send2lcd(unsigned char value)
{
	unsigned char buf = 0;	
	
	buf = value & 0xF0;		/* Filter for high byte */
	buf = (buf>>4)|(0x30);		/* Convert  to ascii code */

	LCD_putc(buf);			/* Show on LCD */

	buf = value & 0x0F;		/* Filter for low byte */
	buf = buf | 0x30;       	/* Convert to ascii code */

	LCD_putc(buf);			/* Show on LCD */
}	

/***************************** Main function *************************************/
void main(void)			
{
	unsigned char sec, min, hour, date, month, year;
	
	PowerOn();  
	
	LCD_row1(); LCD_puts("Date:");	
	LCD_row2(); LCD_puts("Time:");	
	
	//DS1307_settime(0x10,0x27,0x00);		/* Set Time (hh:mm:ss) */
	//DS1307_setdate(0x03,0x08,0x06);  	/* Set Date (dd/mm/yy) */
	
	while(1) 
	{
		/* Get Date & Time */
		sec   = DS1307_get(SEC);	
		min   = DS1307_get(MIN);	
		hour  = DS1307_get(HOUR);
		date  = DS1307_get(DATE);
		month = DS1307_get(MONTH);
		year  = DS1307_get(YEAR);

		/* Show Date in format dd/mm/yr */
		LCD_command(0x86);	/* Set LCD cursor at (1,6) */
		
		send2lcd(date);		/* Show date on LCD */
		
		LCD_putc('/');		
		
		send2lcd(month);	/* Show month on LCD */
		
		LCD_putc('/');	
		
		send2lcd(year);		/* Show year on LCD */

		/* Show Time in format hr:min:sec */	
		LCD_command(0xC6);	/* Set LCD cursor at (2,6) */
		
		send2lcd(hour);		/* Show hour on LCD */
		
		LCD_putc(':');       
		   	
		send2lcd(min);		/* Show min on LCD */
		
		LCD_putc(':');		
		
		send2lcd(sec);		/* Show sec on LCD */
	}	   
} /* End main */
