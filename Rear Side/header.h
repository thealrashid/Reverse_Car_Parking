typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;
typedef char s8;
typedef short int u16;

extern void delay_ms(unsigned int);
extern void delay_sec(unsigned int);
extern void delay_us(unsigned int);

extern void adc_init(void);
extern u32	adc_read(u32);

typedef struct CAN2_MSG
{
    unsigned int id;
    unsigned int dlc;
    unsigned int rtr;
    unsigned int byteA;
    unsigned int byteB;
}CAN2;

extern void can2_init(void);
extern void can2_tx(CAN2);
extern void can2_rx(CAN2 *);
extern void en_can2_rx_intr(void);
