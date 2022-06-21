#include "timer.h"

void init()
{
    PCON |= 0x80;              // 使能波特率倍速位SMOD
    SCON = 0x50;               // 8位数据,可变波特率
    TMOD |= 0x01;              // 设置定时器模式
    TMOD |= 0x20;              // 设置定时器模式
    TL1 = 0xF4;                // 设置定时初始值
    TH1 = 0xF4;                // 设置定时重载值
    ET1 = 0;                   // 禁止定时器1中断
    TR1 = 1;                   // 定时器1开始计时
    TH0 = (65536 - 921) / 256; // 高8位 计时间隔为1ms
    TL0 = (65536 - 921) % 256; // 低8位 计时间隔为1ms
    EA = 1;                    // 允许所有中断
    ES = 1;                    // 开启串口中断
    ET0 = 1;                   // 打开定时器0的中断开关
    TR0 = 1;                   // 开启定时器0计数
}

void time0() interrupt 1 // 计时器0中断函数
{
    TH0 = (65536 - 921) / 256;
    TL0 = (65536 - 921) % 256;
    if (++timer >= 1000) // 1000ms
    {
        timer = 0; // 重置计时器
        if (++sec >= 60)
        {
            sec = 0;
            if (++min >= 60)
            {
                min = 0;
                if (++hour >= 24)
                {
                    hour = 0;
                }
            }
        }
    }
    if (++i >= 8) // 数码管显示位置
        i = 0;
    display(show[i], i);
}