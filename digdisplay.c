#include "reg52.h"
#define FLAGUS 10	 //用于定时模式1 
#define WEI 8   


typedef unsigned int u16;
typedef unsigned char u8;

//使用138译码器
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

u16 flag = 0;        //定时器标志位

u8 i;
u8 s0 = 0, s1 = 0, s2 = 5, s3 = 5, s4 = 9, s5 = 5, s6 = 3 , s7 = 2;


void delayus(u16 value);	    //value = 1 时，大约延时1us。

void opentimer0(void);			//开启定时器0


u8 duanxian[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
                };

void main(void)
{
    opentimer0();
    while(1)
    {
        if(flag >= FLAGUS)
        {
            flag = 0;
            s0++;
            if(s0 >= 10)
            {   s0 = 0;
                s1++;
            }
            if(s1 >= 10)
            {
                s1 = 0;
                s2++;
            }
            if(s2 >= 10)
            {   s2 = 0;
                s3++;
            }
            if(s3 >= 6)
            {   
				s3 = 0;
				s4++;
			}

			if(s4 >= 10)
            {   s4 = 0;
                s5++;
            }
            if(s5 >= 6)
            {
                s5 = 0;
                s6++;
            }
			 if(s6 >= 4)
            {   s6 = 0;
                s7++;
            }
            if(s7 >= 3)
            {
                s7 = 0;
              
            }
        }

        for(i = 0; i < WEI; ++i)
        {
            switch(i)
            {
            case (0):
                LSA = 0;
                LSB = 0;
                LSC = 0; //显示第0位
                P0 = duanxian[s0];
                delayus(1);
                P0 = 0x00;
                break;

            case(1):
                LSA = 1;
                LSB = 0;
                LSC = 0; //显示第1位
                P0 = duanxian[s1];
                delayus(1);
                P0 = 0x00;
                break;
            case(2):
                LSA = 0;
                LSB = 1;
                LSC = 0; //显示第2位
                P0 = duanxian[s2];
                delayus(1);
                P0 = 0x00;
                break;
            case(3):
                LSA = 1;
                LSB = 1;
                LSC = 0; //显示第3位
                P0 = duanxian[s3];
                delayus(1);
                P0 = 0x00;
                break;
			case(4):
				LSA=0;LSB=0;LSC=1;
				P0 = duanxian[s4];
                delayus(1);
                P0 = 0x00;
				break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1;
				P0 = duanxian[s5];
                delayus(1);
                P0 = 0x00;
 				break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1;
					P0 = duanxian[s6];
                delayus(1);
                P0 = 0x00;
				 break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; 
					P0 = duanxian[s7];
                delayus(1);
                P0 = 0x00;
				break;//显示第7位
            }

        }
    }
}

void delayus(u16 value)
{
    u8 i, j;
    for(i = 0; i < 1; i++)
        for(j = 0; j < value; j++);
}

void opentimer0(void)	    //定时器0初始化
{
    TMOD = 0x01;			 //模式1
    TH0 = 0xfc;
    TL0 = 0x20;		  //初值，定时10us
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void int0() interrupt 1		  //定时器0处理函数
{
    TH0 = 0xfc;
    TL0 = 0x20;
    flag ++;
}
