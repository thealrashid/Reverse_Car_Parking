/*can2_driver.c*/
#include<LPC21XX.H>
#include"header.h"

void can2_init(void)
{
    PINSEL1 |= 0x00014000; // P0.23-> RD1 P0.24-> TD1
    VPBDIV = 1; // PCLK = 60MHz
    C2MOD = 1; //Reset mode
    C2BTR = 0x001C001D; // Set bit timing to 125 Kbps
    AFMR = 2; // Accept all incoming messages
    C2MOD = 0; // Cancel normal mode
}

#define TCS ((C2GSR>>3)&1)

void can2_tx(CAN2 m1)
{
    C2TID1 = m1.id;
    C2TFI1 = m1.dlc<<16; // DLC and RTR
    if(m1.rtr == 0) // If data frame
    {
        C2TDA1 = m1.byteA;
        C2TDB1 = m1.byteB;
    }
    else // If remote frame
    {
        C2TFI1 |= (1<<30); // RTR = 1
    }
    C2CMR = 1 | (1<<5); // Start transmission
    while(TCS == 0);
}

#define RBS (C2GSR&1)

void can2_rx(CAN2 *ptr)
{
    while(RBS == 0);
    ptr->id = C2RID; // Get ID
    ptr->dlc = (C2RFS>>16)&0xF; // Extract DLC
    ptr->rtr = (C2RFS>>30)&1; // Extract RTR
    if(ptr->rtr == 0) // If data frame
    {
        ptr->byteA = C2RDA;
        ptr->byteB = C2RDB;
    }
    C2CMR = (1<<2); // Release receiver buffer
}

extern CAN2 n3;
extern int flag;

void CAN2_RX_Handler(void) __irq
{
    n3.id = C2RID;
    n3.dlc = (C2RFS>>16)&0xF;
    n3.rtr = (C2RFS>>30)&1;
    if(n3.rtr == 0)
    {
        n3.byteA = C2RDA;
        n3.byteB = C2RDB;
    }
    C2CMR = (1<<2);
    flag = 1;
    VICVectAddr = 0;
}

void en_can2_rx_intr(void)
{
    VICIntSelect = 0;
    VICVectAddr1 = (int)CAN2_RX_Handler;
    VICVectCntl1 = 27 | (1<<5);
    VICIntEnable |= (1<<27);
    C2IER = 1; // Receiver interrupt enable
}

			