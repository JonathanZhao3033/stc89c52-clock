#include "reg52.h"
#define VAL 100	 //用于定时模式1    


typedef unsigned int u16;
typedef unsigned char u8;

sbit a = P2 ^ 5;
sbit b = P2 ^ 6;

u16 times = 0;
u8 timekeeping = 0;
u8 i;
u8 s0;
u8 s1;

void delay(u16 value);	    //value = 1 时，大约延时1us。

void opentimer0(void);


u8 duanxian[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
                };

void main(void)
{
    opentimer0();
    while(1)
    {
        if(times == VAL)
        {
            times = 0;
            timekeeping ++;
            if(timekeeping == 60)
            {
                timekeeping = 0;
            }
        }

        s0 = timekeeping / 10;
        s1 = timekeeping % 10;


        for(i = 0; i < 2; i++)
        {
            switch(i)
            {
            case (0):
                a = 1;
                b = 0;
                P0 = duanxian[s0];
                delay(1);
                P0 = 0x00;
                break;

            case(1):
                a = 0;
                b = 1;
                P0 = duanxian[s1];
                delay(1);
                P0 = 0x00;
                break;
            }

        }
    }
}

void delay(u16 value)
{
    u8 i, j;
    for(i = 0; i < 1; i++)
        for(j = 0; j < value; j++);
}

void opentimer0(void)	    //定时器0初始化
{
    TMOD = 0x01;			 //模式1
    TH0 = 0xdc;
    TL0 = 0x08;		  //初值，定时10000us  10ms
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void int0() interrupt 1		  //定时器0  模式1处理函数
{
    TH0 = 0xdc;
    TL0 = 0x08;
    times ++;
}
