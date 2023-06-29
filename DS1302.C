#include "DS1302.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include "OLED.h"

#include "DS1302.h"


/**************宏定义***************/
#define DS_RST      BIT7    /* DS_RST = P8.7 */
#define DS_SCL      BIT5    /* DS_SCL = P8.5 */
#define DS_SDA      BIT6    /* DS_SDA = P8.6 */
#define DS_RST_IN   P8DIR   &= ~DS_RST
#define DS_RST_OUT  P8DIR   |= DS_RST
#define DS_RST0     P8OUT   &= ~DS_RST
#define DS_RST1     P8OUT   |= DS_RST
#define DS_SCL_IN   P8DIR   &= ~DS_SCL
#define DS_SCL_OUT  P8DIR   |= DS_SCL
#define DS_SCL0     P8OUT   &= ~DS_SCL
#define DS_SCL1     P8OUT   |= DS_SCL
#define DS_SDA_IN   P8DIR   &= ~DS_SDA
#define DS_SDA_OUT  P8DIR   |= DS_SDA
#define DS_SDA0     P8OUT   &= ~DS_SDA
#define DS_SDA1     P8OUT   |= DS_SDA
#define DS_SDA_BIT  (P8IN & DS_SDA)


/* DS1302地址定义 */
#define ds1302_sec_add      0x80    /* 秒数据地址 */
#define ds1302_min_add      0x82    /* 分数据地址 */
#define ds1302_hr_add       0x84    /* 时数据地址 */
#define ds1302_date_add     0x86    /* 日数据地址 */
#define ds1302_month_add    0x88    /* 月数据地址 */
#define ds1302_day_add      0x8a    /* 星期数据地址 */
#define ds1302_year_add     0x8c    /* 年数据地址 */
#define ds1302_control_add  0x8e    /* 控制数据地址 */
#define ds1302_charger_add  0x90
#define ds1302_clkburst_add 0xbe


/* 向DS1302写入一个字节数据 */
void W_Data( unsigned char addr, unsigned char data )
{
    int i;
        DS_RST_OUT;DS_SCL_OUT;DS_SDA_OUT;

    DS_RST0;            /* 停止DS1302总线 */
    DS_SCL0;            /* 清零时钟线 */
    Clock_Delay1us( 10 );
    DS_RST1;            /* 启动DS1302总线 */
    addr        = addr & 0xFE;  /* 最低位置零，写数据 */
    DS_SDA_OUT;
    for ( i = 0; i < 8; i++ )       /* 写地址 */
    {
        DS_SCL0;
        if ( addr & 0x01 )
            DS_SDA1;
        else
            DS_SDA0;

        addr        = addr >> 1;
        DS_SCL1;    /* 产生时钟在上升沿输出数据到DS1302 */
        Clock_Delay1us( 9 );
    }
    for ( i = 0; i < 8; i++ )       /* 写数据 */
    {
        DS_SCL0;
        if ( data & 0x01 )
            DS_SDA1;
        else
            DS_SDA0;
        data        = data >> 1;
        DS_SCL1;    /* 产生时钟在上升沿输出数据到DS1302 */
        Clock_Delay1us( 9 );
    }
    DS_RST0;                 /* 停止DS1302总线 */
}


/* 从DS1302读出一个字节数据 */
unsigned char R_Data( unsigned char addr )
{
    unsigned char i, temp;
        DS_RST_OUT;DS_SCL_OUT;DS_SDA_OUT;

    DS_RST0;            /* 停止DS1302总线 */
    DS_SCL0;            /* 清零时钟线 */
    Clock_Delay1us( 10 );
    DS_RST1;            /* 启动DS1302总线 */
    addr        = addr | 0x01;  /* 最低位置高，读数据 */
    DS_SDA_OUT;
    for ( i = 0; i < 8; i++ )       /* 写地址 */
    {
        DS_SCL0;
        if ( addr & 0x01 )
            DS_SDA1;
        else
            DS_SDA0;
        addr        = addr >> 1;
        DS_SCL1;    /* 产生时钟在上升沿输出数据到DS1302 */
        Clock_Delay1us( 9 );
    }
    DS_SDA_IN;
    for ( i = 0; i < 8; i++ )       /* 读数据 */
    {
        if ( DS_SDA_BIT )
            temp |= 0x80;
        else
            temp &= 0x7F;
        DS_SCL1;    /* 产生时钟在下升沿输出数据到DS1302 */
        temp        = temp >> 1;
        DS_SCL0;
        Clock_Delay1us( 9 );
    }
    DS_RST0;                 /* 停止DS1302总线 */
    return(temp);
}


/*******************************************
 * 函数名称：Set_DS1302
 * 功    能：设置DS1302内部的时间
 * 参    数：ptr--指向存放数据地址的指针
 * 返回值  ：无
 * 说明    ：写入数据的格式：
 *          秒 分 时 日 月 星期 年  【共7个字节】
 ********************************************/
void Set_DS1302( unsigned char *ptr )
{
    unsigned char   i;
    unsigned char   addr = 0x80;

    W_Data( 0x8e, 0x00 );                           /* 允许写入 */

    for ( i = 7; i > 0; i-- )
    {
        W_Data( addr, *ptr++ );
        addr += 2;
    }
    W_Data( 0x8e, 0x80 );                           /* 禁止 */
}


/* 从DS302读出时钟数据 */
void DS1302_Read_Time( unsigned char *ptr )
{
    ptr[1]  = R_Data( ds1302_year_add );            /* 年 */
    ptr[2]  = R_Data( ds1302_month_add );           /* 月 */
    ptr[3]  = R_Data( ds1302_date_add );            /* 日 */
    ptr[4]  = R_Data( ds1302_hr_add );              /* 时 */
    ptr[5]  = R_Data( ds1302_min_add );             /* 分 */
    ptr[6]  = (R_Data( ds1302_sec_add ) ) & 0x7f;   /* 秒，屏蔽秒的第7位，避免超出59 */
    ptr[7]  = R_Data( ds1302_day_add );             /* 周 */
}


/* 获取时间 */
void DS1302_read_time( struct ds1302time *p )
{
    /* 年月日 时分秒 星期 */
    unsigned char time_buf[8] = { 0x20, 0x20, 0x03, 0x03, 0x23, 0x59, 0x55, 0x02 };


    DS1302_Read_Time( time_buf ); /* 读取 */

    p->year     = 2000 + (time_buf[1] >> 4) * 10 + (time_buf[1] & 0x0f);
    p->mouth    = (time_buf[2] >> 4) * 10 + (time_buf[2] & 0x0f);
    p->day      = (time_buf[3] >> 4) * 10 + (time_buf[3] & 0x0f);

    p->hour     = (time_buf[4] >> 4) * 10 + (time_buf[4] & 0x0f);
    p->minute   = (time_buf[5] >> 4) * 10 + (time_buf[5] & 0x0f);
    p->second   = (time_buf[6] >> 4) * 10 + (time_buf[6] & 0x0f);

    p->week = (time_buf[7] >> 4) * 10 + (time_buf[7] & 0x0f);
}


/* 写入时间 */
void DS1302_write_time( struct ds1302time *p )
{
    /* 年月日 时分秒 星期 */
    unsigned char time_buf[8] = { 0x20, 0x20, 0x03, 0x03, 0x23, 0x59, 0x55, 0x02 };

    time_buf[1] = p->year % 100 / 10 * 16 + p->year % 100 % 10;
    time_buf[2] = p->mouth % 100 / 10 * 16 + p->mouth % 100 % 10;
    time_buf[3] = p->day % 100 / 10 * 16 + p->day % 100 % 10;
    time_buf[4] = p->hour % 100 / 10 * 16 + p->hour % 100 % 10;
    time_buf[5] = p->minute % 100 / 10 * 16 + p->minute % 100 % 10;
    time_buf[6] = p->second % 100 / 10 * 16 + p->second % 100 % 10;
    time_buf[7] = p->week % 100 / 10 * 16 + p->week % 100 % 10;

    W_Data( ds1302_control_add, 0x00 );             /* 关闭写保护 */
    W_Data( ds1302_sec_add, 0x80 );                 /* 暂停时钟 */
    /* DS1302_Write_Byte(ds1302_charger_add, 0xA9);      //涓流充电 */
    W_Data( ds1302_year_add, time_buf[1] );         /* 年 */
    W_Data( ds1302_month_add, time_buf[2] );        /* 月 */
    W_Data( ds1302_date_add, time_buf[3] );         /* 日 */
    W_Data( ds1302_hr_add, time_buf[4] );           /* 时 */
    W_Data( ds1302_min_add, time_buf[5] );          /* 分 */
    W_Data( ds1302_sec_add, time_buf[6] );          /* 秒 */
    W_Data( ds1302_day_add, time_buf[7] );          /* 周 */
    W_Data( ds1302_control_add, 0x80 );             /* 打开写保护 */
}


/*
 * 由年月日获取星期 https://www.cnblogs.com/fengbohello/p/3264300.html
 * 返回1到7 代表星期一到星期天
 */
int getWeekdayByYearday( int iY, int iM, int iD )
{
    int iWeekDay = -1;
    if ( 1 == iM || 2 == iM )
    {
        iM += 12;
        iY--;
    }
    iWeekDay = (iD + 1 + 2 * iM + 3 * (iM + 1) / 5 + iY + iY / 4 - iY / 100 + iY / 400) % 7;
    if ( iWeekDay == 0 )
        iWeekDay = 7;
    return(iWeekDay);
}

struct ds1302time time_now;
int mb=0;
void get_time(void)
{
    DS1302_read_time(&time_now);
    mb=mb+1;
    if(mb==3600000){
        mb=0;
    }
}

void TIME_SET (struct ds1302time*time_set)
{
    time_set->day = 28;
    time_set->hour = 6;
    time_set->minute = 51;
    time_set->mouth = 2;
    time_set->second = 50;
    time_set->week = 4;
    time_set->year = 2020;
}

int data_buf12[7];
int data_buf[7];
void data_get(int *data24,int *data12)
{
    //年月日时分秒周  24时
    data24[0] = time_now.year;
    data24[1] = time_now.mouth;
    data24[2] = time_now.day;
    data24[3] = time_now.hour;
    data24[4] = time_now.minute;
    data24[5] = time_now.second;
    data24[6] = time_now.week;

    if(data24[3]>12){
        data12[3] = time_now.hour - 12;
    }
    else{
        data12[3] = time_now.hour ;
    }
    data12[0] = time_now.year;
    data12[1] = time_now.mouth;
    data12[2] = time_now.day;
    data12[4] = time_now.minute;
    data12[5] = time_now.second;
    data12[6] = time_now.week;
}


// 12 or 24 小时制切换
void time_transform(void)
{
    unsigned char AP,TS;
    unsigned char time_mode,time_hour;
    AP = R_Data(ds1302_hr_add)>>5 & 0x01; //0->am 1->pm
    TS = R_Data(ds1302_hr_add) & 0X80;//0->24 1->12
    if(TS == 0x00 )//24转换12
    {
        if(time_now.hour <=12)
        {
            time_hour = time_now.hour;
            time_mode= time_hour % 100 / 10 * 16 + time_hour % 100 % 10;
            time_mode |= 0x80;
            W_Data( ds1302_control_add, 0x00 );
            W_Data(ds1302_hr_add, time_mode);
            W_Data( ds1302_control_add, 0x80 );

        }
        else
        {
            time_hour=time_now.hour - 12;
            time_mode= time_hour % 100 / 10 * 16 + time_hour % 100 % 10;
            time_mode = 0xA0 | time_mode;
            OLED_ShowNum(54, 2, R_Data(ds1302_hr_add), 8, 12);
            W_Data( ds1302_control_add, 0x00 );
            W_Data(ds1302_hr_add, 0xC0);
            W_Data( ds1302_control_add, 0x80 );
          //  OLED_ShowNum(54, 0, R_Data(ds1302_hr_add), 8, 12);//时
        }
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
    else if(TS != 0X00) //12转换24
    {
//        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        if(AP ==0x01)
        {
            time_hour=time_now.hour + 12;
            time_mode= time_hour % 100 / 10 * 16 + time_hour % 100 % 10;
            time_mode &= 0x3f;
            W_Data( ds1302_control_add, 0x00 );
            W_Data(ds1302_hr_add, time_mode);
            W_Data( ds1302_control_add, 0x80 );

        }
        else if(AP ==0x00)
        {
            time_hour=time_now.hour ;
            time_mode= time_hour % 100 / 10 * 16 + time_hour % 100 % 10;
            time_mode &= 0x3f;
            W_Data( ds1302_control_add, 0x00 );
            W_Data(ds1302_hr_add, time_mode);
            W_Data( ds1302_control_add, 0x80 );
        }

    }

}



