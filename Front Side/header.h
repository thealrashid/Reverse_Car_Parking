typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;
typedef char s8;
typedef short int u16;

extern void delay_ms(unsigned int);
extern void delay_sec(unsigned int);
extern void delay_us(unsigned int);

extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_init(void);
extern void lcd_string(char *);
extern void lcd_integer(int);
extern void lcd_float(float);
extern void custom_symbol(unsigned char *, unsigned char);

extern void config_vic_eint(void);
extern void en_eint(void);

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
