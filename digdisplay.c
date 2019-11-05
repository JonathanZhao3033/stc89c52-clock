#include "reg52.h"
#define FLAGUS 10	 //���ڶ�ʱģʽ1 
#define WEI 8   


typedef unsigned int u16;
typedef unsigned char u8;

//ʹ��138������
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

u16 flag = 0;        //��ʱ����־λ

u8 i;
u8 s0 = 0, s1 = 0, s2 = 5, s3 = 5, s4 = 9, s5 = 5, s6 = 3 , s7 = 2;


void delayus(u16 value);	    //value = 1 ʱ����Լ��ʱ1us��

void opentimer0(void);			//������ʱ��0


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
                LSC = 0; //��ʾ��0λ
                P0 = duanxian[s0];
                delayus(1);
                P0 = 0x00;
                break;

            case(1):
                LSA = 1;
                LSB = 0;
                LSC = 0; //��ʾ��1λ
                P0 = duanxian[s1];
                delayus(1);
                P0 = 0x00;
                break;
            case(2):
                LSA = 0;
                LSB = 1;
                LSC = 0; //��ʾ��2λ
                P0 = duanxian[s2];
                delayus(1);
                P0 = 0x00;
                break;
            case(3):
                LSA = 1;
                LSB = 1;
                LSC = 0; //��ʾ��3λ
                P0 = duanxian[s3];
                delayus(1);
                P0 = 0x00;
                break;
			case(4):
				LSA=0;LSB=0;LSC=1;
				P0 = duanxian[s4];
                delayus(1);
                P0 = 0x00;
				break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1;
				P0 = duanxian[s5];
                delayus(1);
                P0 = 0x00;
 				break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1;
					P0 = duanxian[s6];
                delayus(1);
                P0 = 0x00;
				 break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; 
					P0 = duanxian[s7];
                delayus(1);
                P0 = 0x00;
				break;//��ʾ��7λ
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

void opentimer0(void)	    //��ʱ��0��ʼ��
{
    TMOD = 0x01;			 //ģʽ1
    TH0 = 0xfc;
    TL0 = 0x20;		  //��ֵ����ʱ10us
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void int0() interrupt 1		  //��ʱ��0������
{
    TH0 = 0xfc;
    TL0 = 0x20;
    flag ++;
}
