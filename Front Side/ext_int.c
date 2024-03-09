/*ext_int1.c*/
#include<LPC21XX.H>
#include"header.h"

CAN2 n1, n2;
extern int f;  
   
void EINT1_Handler(void) __irq
{
    EXTINT |= 0x2;
    if(f == 0)
    {
        f = 1;
        n1.id = 0x123;
        n1.dlc = 4;
        n1.rtr = 1;
        can2_tx(n1);
    }
    else
    {
        f = 0;
        n2.id = 0x124;
        n2.dlc = 1;
        n2.rtr = 0;
        n2.byteB = 0;
        n2.byteA = 0x1;
        can2_tx(n2);
    }
    VICVectAddr = 0;
}

void config_vic_eint(void)
{
    VICIntSelect = 0;
    VICVectCntl0 = 15 | (1<<5);
    VICVectAddr0 = (int)EINT1_Handler;
    VICIntEnable |= (1<<15);
}

void en_eint(void)
{
    EXTMODE = 0x2;
    EXTPOLAR = 0;
    PINSEL0 |= 0x20000000;
}