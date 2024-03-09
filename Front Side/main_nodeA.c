/* Reverse Car Parking Assistance System */
/*main_nodeA.c*/
#include<LPC21XX.H>
#include"header.h"

#define BUZ (1<<21)
#define LED (1<<17)

CAN2 n3;
int flag = 0, f = 0;

int main()
{
    int d;
   
    IODIR0 = LED | BUZ;
    IOSET0 = LED;
	IOCLR0 = BUZ;
   
    can2_init();
    en_can2_rx_intr();
    config_vic_eint();
    en_eint();
    lcd_init();
   
    while(1)
    {
        if(f == 1)
        {
            IOCLR0 = LED;
			if(flag == 1)
            {
                flag = 0;
                d = n3.byteA;
                lcd_cmd(0x01);
                lcd_integer(d);
               
                if((d <= 400) && (d > 300))
                {
                    while((flag == 0) && (f == 1))
                    {
                        IOSET0 = BUZ;
                        delay_ms(100);
						IOCLR0 = BUZ;
                        delay_ms(1500);
                    }
                }
                else if((d <= 300) && (d > 200))
                {
                    while((flag == 0) && (f == 1))
                    {
                        IOSET0 = BUZ;
                        delay_ms(100);
						IOCLR0 = BUZ;
                        delay_ms(1000);
                    }
                }
                else if((d <= 200) && (d > 100))
                {
                    while((flag == 0) && (f == 1))
                    {
                        IOSET0 = BUZ;
                        delay_ms(100);
						IOCLR0 = BUZ;
                        delay_ms(500);
                    }
                }
                else if((d <= 100) && (d > 50))
                {
                    while((flag == 0) && (f == 1))
                    {
                        IOSET0 = BUZ;
                        delay_ms(100);
						IOCLR0 = BUZ;
                        delay_ms(100);
                    }
                }
                else if(d <= 50)
                {
                    while((flag == 0) && (f == 1))
                    {
                        IOSET0 = BUZ;
                    }
                }
            }
        }
        else
        {
            IOSET0 = LED;
			IOCLR0 = BUZ;
        }
    }
}
