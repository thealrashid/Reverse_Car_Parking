/*main_nodeB.c*/
#include"header.h"

CAN2 n3, n4;
int flag = 0;

int main()
{
    adc_init();
    can2_init();
    en_can2_rx_intr();
   
   while(1)
    {
        if(flag == 1)
        {
            flag = 0;
            if(n3.rtr == 1)
            {
                n4.id = n3.id;
                n4.dlc = n3.dlc;
                n4.rtr = 0;
                n4.byteB = 0;
                while(flag == 0)
                {
                    n4.byteA = adc_read(2);
                    can2_tx(n4);
                    delay_ms(100);
                }
            }
        }
    }
}
