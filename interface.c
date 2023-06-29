#include "DS1302.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include "OLED.h"
#include "interface.h"
#include "key.h"

void HOME(void){
            data_get(data_buf,data_buf12);
            if (k==0){
                            k=1;
                            OLED_Clear();
                        }
            if(C61_flag ==0){
                OLED_ShowChinese(0, 0, 22, 12);    //时区
                OLED_ShowChinese(12, 0, 23, 12);
                OLED_ShowString(24, 0,":", 12);
                OLED_ShowNum_buquan(54, 0, data_buf[3]);//时
                OLED_ShowString(70, 0,":", 12);
                OLED_ShowNum_buquan(82, 0, data_buf[4]);//分
                OLED_ShowString(98, 0,":", 12);
                OLED_ShowNum_buquan(110, 0, data_buf[5]);//秒

                OLED_ShowNum(4, 3, data_buf[0], 4, 12);//年
                OLED_ShowChinese(30, 3, 3, 12);
                OLED_ShowNum_buquan(44, 3, data_buf[1]);//月
                OLED_ShowChinese(58, 3, 4, 12);
                OLED_ShowNum_buquan(72, 3, data_buf[2]);//日
                OLED_ShowChinese(86, 3, 5, 12);
                OLED_ShowChinese(100, 3, 6, 12);

                OLED_ShowChinese(2, 6, 7, 12);//闹
                OLED_ShowChinese(14, 6, 8, 12);//钟
                OLED_ShowString(26, 6,":", 12);
                OLED_ShowChinese(38, 6, 6, 12);
                switch(clocktime[2]){
                case 1:
                    OLED_ShowChinese(50, 6, 9, 12);
                    break;
                case 2:
                    OLED_ShowChinese(50, 6, 10, 12);
                    break;
                case 3:
                    OLED_ShowChinese(50, 6, 11, 12);
                    break;
                case 4:
                    OLED_ShowChinese(50, 6, 12, 12);
                    break;
                case 5:
                    OLED_ShowChinese(50, 6, 13, 12);
                    break;
                case 6:
                    OLED_ShowChinese(50, 6, 14, 12);
                    break;
                case 7:
                    OLED_ShowChinese(50, 6, 5, 12);
                    break;
                }
                OLED_ShowNum_buquan(66, 6, clocktime[1]);//时
                OLED_ShowChinese(82, 6, 0, 12);
                OLED_ShowNum_buquan(98, 6, clocktime[0]);//分
                OLED_ShowChinese(114, 6, 1, 12);
                }
                else if (C61_flag ==1){
                    OLED_ShowChinese(0, 0, 22, 12);    //时区
                    OLED_ShowChinese(12, 0, 23, 12);
                    OLED_ShowString(24, 0,":", 12);
                    OLED_ShowNum_buquan(54, 0, data_buf12[3]);//时
                    OLED_ShowString(70, 0,":", 12);
                    OLED_ShowNum_buquan(82, 0, data_buf12[4]);//分
                    OLED_ShowString(98, 0,":", 12);
                    OLED_ShowNum_buquan(110, 0, data_buf12[5]);//秒

                    OLED_ShowNum(4, 3, data_buf12[0], 4, 12);//年
                    OLED_ShowChinese(30, 3, 3, 12);
                    OLED_ShowNum_buquan(44, 3, data_buf12[1]);//月
                    OLED_ShowChinese(58, 3, 4, 12);
                    OLED_ShowNum_buquan(72, 3, data_buf12[2]);//日
                    OLED_ShowChinese(86, 3, 5, 12);
                    OLED_ShowChinese(100, 3, 6, 12);

                    OLED_ShowChinese(2, 6, 7, 12);//闹
                    OLED_ShowChinese(14, 6, 8, 12);//钟
                    OLED_ShowString(26, 6,":", 12);
                    OLED_ShowChinese(38, 6, 6, 12);
                    switch(clocktime[2]){
                    case 1:
                        OLED_ShowChinese(50, 6, 9, 12);
                        break;
                    case 2:
                        OLED_ShowChinese(50, 6, 10, 12);
                        break;
                    case 3:
                        OLED_ShowChinese(50, 6, 11, 12);
                        break;
                    case 4:
                        OLED_ShowChinese(50, 6, 12, 12);
                        break;
                    case 5:
                        OLED_ShowChinese(50, 6, 13, 12);
                        break;
                    case 6:
                        OLED_ShowChinese(50, 6, 14, 12);
                        break;
                    case 7:
                        OLED_ShowChinese(50, 6, 5, 12);
                        break;
                    }
                    OLED_ShowNum_buquan(66, 6, clocktime[1]);//时
                    OLED_ShowChinese(82, 6, 0, 12);
                    OLED_ShowNum_buquan(98, 6, clocktime[0]);//分
                    OLED_ShowChinese(114, 6, 1, 12);
                }

                switch(data_buf[6]){
                case 1:
                    OLED_ShowChinese(112, 3, 9, 12);
                    break;
                case 2:
                    OLED_ShowChinese(112, 3, 10, 12);
                    break;
                case 3:
                    OLED_ShowChinese(112, 3, 11, 12);
                    break;
                case 4:
                    OLED_ShowChinese(112, 3, 12, 12);
                    break;
                case 5:
                    OLED_ShowChinese(112, 3, 13, 12);
                    break;
                case 6:
                    OLED_ShowChinese(112, 3, 14, 12);
                    break;
                case 7:
                    OLED_ShowChinese(112, 3, 5, 12);
                    break;


        }
}
void Menu(void){
/*清屏函数*/
    if (k==0){
                    k=1;
                    OLED_Clear();
                }
  /*-----------*/
    OLED_ShowNum(0, 0, 1, 1, 12);
    OLED_ShowChar(6,0,'.',12);
    OLED_ShowChinese(18, 0, 2, 12);
    OLED_ShowChinese(30, 0, 15, 12);    //秒表

    OLED_ShowNum(0, 2, 2, 1, 12);
    OLED_ShowChar(6,2,'.',12);
    OLED_ShowChinese(18, 2, 7, 12);
    OLED_ShowChinese(30, 2, 8, 12);    //闹钟

    OLED_ShowNum(0, 4, 3, 1, 12);
    OLED_ShowChar(6,4,'.',12);
    OLED_ShowChinese(18, 4, 16, 12);
    OLED_ShowChinese(30, 4, 17, 12);
    OLED_ShowChinese(42, 4, 0, 12);
    OLED_ShowChinese(54, 4, 18, 12);    //世界时钟

    OLED_ShowNum(0, 6, 4, 1, 12);
    OLED_ShowChar(6,6,'.',12);
    OLED_ShowChinese(18, 6, 19, 12);
    OLED_ShowChinese(30, 6, 20, 12);
    OLED_ShowChinese(42, 6, 21, 12);    //计时器
    Clock_Delay1ms(250);
    if(C6_flag == 0 ){
        OLED_Clearline(0);
        OLED_Clearline(1);
    }
    else if (C6_flag == 1 ){
        OLED_Clearline(2);
        OLED_Clearline(3);
    }
    else if (C6_flag == 2 ){
        OLED_Clearline(4);
        OLED_Clearline(5);
    }
    else if (C6_flag == 3 ){
        OLED_Clearline(6);
        OLED_Clearline(7);
    }
    Clock_Delay1ms(250);
}

int second_zong=1;
void Countdown(void){
    /*清屏函数*/
        if (k==0){
                        k=1;
                        OLED_Clear();
                    }
      /*-----------*/
    int second_all_dj;
    int hour_dj=(second_zong)/3600;
    int minute_dj=(second_zong)%3600/60;
    int second_dj=(second_zong)%60;
    if(C4_flag==1&C8_flag==0){
    if(second_zong>0){
        second_all_dj=0.01*mb;
        if(second_zong>=second_all_dj){
        hour_dj=(second_zong-second_all_dj)/3600;
        minute_dj=(second_zong-second_all_dj)%3600/60;
        second_dj=(second_zong-second_all_dj)%60;
        OLED_ShowNum_buquan(4,0,hour_dj);
        OLED_ShowString(16, 0,":", 12);
        OLED_ShowNum_buquan(22,0,minute_dj);
        OLED_ShowString(34, 0,":", 12);
        OLED_ShowNum_buquan(40,0,second_dj);}
        else{
            OLED_ShowNum_buquan(4,0,0);
            OLED_ShowString(16, 0,":", 12);
            OLED_ShowNum_buquan(22,0,0);
            OLED_ShowString(34, 0,":", 12);
            OLED_ShowNum_buquan(40,0,0);
            OLED_ShowString(0, 3,"Time flies!", 12);
            OLED_ShowString(0, 6,"Countdown over!", 12);
        }
    }
    else{
        OLED_ShowNum_buquan(4,0,0);
        OLED_ShowString(16, 0,":", 12);
        OLED_ShowNum_buquan(22,0,0);
        OLED_ShowString(34, 0,":", 12);
        OLED_ShowNum_buquan(40,0,0);
        OLED_ShowString(0, 3,"Time flies!", 12);
        OLED_ShowString(0, 6,"Countdown over!", 12);
    }
    }
    else {
        if(second_zong>0){
        OLED_ShowNum_buquan(4,0,hour_dj);
        OLED_ShowString(16, 0,":", 12);
        OLED_ShowNum_buquan(22,0,minute_dj);
        OLED_ShowString(34, 0,":", 12);
        OLED_ShowNum_buquan(40,0,second_dj);}
        else{
            OLED_ShowNum_buquan(4,0,0);
            OLED_ShowString(16, 0,":", 12);
            OLED_ShowNum_buquan(22,0,0);
            OLED_ShowString(34, 0,":", 12);
            OLED_ShowNum_buquan(40,0,0);
        }
    }
    if(C8_flag == 1&C4_flag==0 ){
        OLED_ShowString(40, 2,"--", 12);
    }
    else if (C8_flag == 2&C4_flag==0 ){
        OLED_ShowString(22, 2,"--", 12);
    }
    else if (C8_flag == 3&C4_flag==0 ){
        OLED_ShowString(4, 2,"--", 12);
    }
}

void Worldtime(void){
    //世界时钟
    /*清屏函数*/
        if (k==0){
                        k=1;
                        OLED_Clear();
                    }
    /*-----------*/
    data_get(data_buf,data_buf12);
    int hour_hsd;
    int hour_ld;
    OLED_ShowChinese(0, 0, 22, 12);    //北京
    OLED_ShowChinese(12, 0, 23, 12);
    OLED_ShowString(24, 0,":", 12);
    OLED_ShowNum_buquan(30, 0, data_buf[3]);
    OLED_ShowString(42, 0,":", 12);
    OLED_ShowNum_buquan(48, 0, data_buf[4]);
    if(data_buf[3]>=12){
        hour_hsd=data_buf[3]-12;
    }
    else{
        hour_hsd=data_buf[3]+12;
    }
    OLED_ShowChinese(0, 2, 24, 12);    //华盛顿
    OLED_ShowChinese(12, 2, 25, 12);
    OLED_ShowChinese(24, 2, 26, 12);
    OLED_ShowString(36, 2,":", 12);
    OLED_ShowNum_buquan(42, 2, hour_hsd);
    OLED_ShowString(54, 2,":", 12);
    OLED_ShowNum_buquan(60, 2, data_buf[4]);
    if(data_buf[3]>=7){
        hour_ld=data_buf[3]-7;
    }
    else{
        hour_ld=data_buf[3]+17;
    }
    OLED_ShowChinese(0, 4, 27, 12);    //伦敦
    OLED_ShowChinese(12, 4, 28, 12);
    OLED_ShowString(24, 4,":", 12);
    OLED_ShowNum_buquan(30, 4, hour_ld);
    OLED_ShowString(42, 4,":", 12);
    OLED_ShowNum_buquan(48, 4, data_buf[4]);
}

int clocktime[3] = {0,0,1};//分 时 周
void Alarmclock(void){
    /*清屏函数*/
        if (k==0){
                        k=1;
                        OLED_Clear();
                    }
      /*-----------*/
        OLED_ShowChinese(0, 0, 6, 12);  //周
        OLED_ShowString(40, 0,":", 12);

        if(C81_flag==1){
            OLED_ShowString(46, 2,"__", 12);    //选中分钟
        }

        else if(C81_flag==2){
            OLED_ShowString(28, 2,"__", 12);   //选中小时
        }

        else if(C81_flag==3){
            OLED_ShowString(12, 2,"__", 12);    //选中星期
        }
        OLED_ShowNum(28, 0, clocktime[1], 2, 12); //小时
        OLED_ShowNum(46, 0, clocktime[0], 2, 12); //分钟
        if(C41_flag == 1){
            OLED_ShowChar(64, 4, 'O', 12);
            OLED_ShowChar(70, 4, 'N', 12);
        }
        else if(C41_flag == 0){
            OLED_ShowChar(64, 4, 'O', 12);
            OLED_ShowChar(70, 4, 'F', 12);
            OLED_ShowChar(76, 4, 'F', 12);
        }

            switch(clocktime[2]){
            case 1:
                OLED_ShowChinese(12, 0, 9, 12);
                break;
            case 2:
                OLED_ShowChinese(12, 0, 10, 12);
                break;
            case 3:
                OLED_ShowChinese(12, 0, 11, 12);
                break;
            case 4:
                OLED_ShowChinese(12, 0, 12, 12);
                break;
            case 5:
                OLED_ShowChinese(12, 0, 13, 12);
                break;
            case 6:
                OLED_ShowChinese(12, 0, 14, 12);
                break;
            case 7:
                OLED_ShowChinese(12, 0, 5, 12);
                break;
            }

}





