#include <STC15F2K60S2.H>

#define uint unsigned int
#define uchar unsigned char

uint T_01ms = 1;
uint T_20ms_duty = 0;
uint count = 1;

void Initsys();
void SelectHC138(uchar channel);

void InitTimer0();

void main()
{
	InitTimer0();
	Initsys();
	SelectHC138(4);
	while(1)
	{
		
		if(T_01ms <= count)
		{
			P0 = 0XFE;
		}
		else if(T_01ms > count)
		{
			P0 = 0XFF;
		}
		else if(T_01ms == 141)
		{
			count++;
			T_01ms = 0;
		}
		else if(count == 142)
		{
			count = 0;
		}
	}
}

void InitTimer0()
{
	TMOD = 0x01;
	TH0 = (65535 - 100) / 256;
	TL0 = (65535 - 100) % 256;
	
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}

void ServiceTimer0() interrupt 1
{
	TH0 = (65535 - 100) / 256;
	TL0 = (65535 - 100) % 256;
	
	T_01ms++;
}

//配置HC138
void SelectHC138(uchar channel)
{
	switch(channel)
	{
		case 4:    //LED
			P2 = (P2 & 0X1F) | 0X80;
		break;
		case 5:    //蜂鸣器和继电器
			P2 = (P2 & 0X1F) | 0Xa0;
		break;
		case 6:    //位码
			P2 = (P2 & 0X1F) | 0Xc0;
		break;
		case 7:    //段码
			P2 = (P2 & 0X1F) | 0Xe0;
		break;
		case 0:    //锁住所有寄存器
			P2 = (P2 & 0X1F) | 0X00;
		break;
	}
}

//系统初始化
void Initsys()
{
	SelectHC138(5);
	P0 = 0X00;//关闭蜂鸣器和继电器
	SelectHC138(4);
	P0 = 0XFF;//关闭LED
	
	SelectHC138(6);
	P0 = 0XFF; //选择所有数码管
	SelectHC138(7);
	P0 = 0XFF; //关闭所有数码管
}
