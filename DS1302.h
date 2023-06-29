#ifndef __DS1302_H
#define __DS1302_H

#include "msp.h"
#include "Clock.h"

struct ds1302time
{
    int year;
    unsigned char   mouth;
    unsigned char   day;
    unsigned char   week;
    unsigned char   hour;
    unsigned char   minute;
    unsigned char   second;
};
unsigned char R_Data( unsigned char addr );
void W_Data( unsigned char addr, unsigned char data );
void DS1302_Read_Time( unsigned char *ptr );

void DS1302_read_time( struct ds1302time *p );//获取时间
void DS1302_write_time( struct ds1302time *p );//写入时间
void get_time(void);//中断函数主体
void TIME_SET (struct ds1302time *time_set);
void data_get(int *data,int *data12);
int getWeekdayByYearday( int iY, int iM, int iD );//获取星期几
void time_transform(void);

extern int mb;
extern struct ds1302time time_now;
extern int data_buf[7];
extern int data_buf12[7];

#endif



