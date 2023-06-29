#include "msp.h"
#include "key.h"
#include "Clock.h"
#include "DS1302.h"
#include "OLED.h"
#include "interface.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void PORT1_IRQHandler(void);
void PORT4_IRQHandler(void);


void key_init(void){
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN6);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN7);
}
int flag = 0;
int C8_flag =0;
int C81_flag =0;
int C1_flag = 0;
int C2_flag =0;
int C3_flag =0;
int C4_flag = 0;
int C41_flag = 0;
int C5_flag =0;
int C6_flag =0;
int C61_flag =0;
int C7_flag = 0;

void key_scan_INTERRUPT(void) //按键扫描中断
{
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN6);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN7);

    GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN4, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN0, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN2, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN3, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN4, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN5, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN6, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);



    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);


    GPIO_registerInterrupt(GPIO_PORT_P1, PORT1_IRQHandler);
    GPIO_registerInterrupt(GPIO_PORT_P4, PORT4_IRQHandler);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN6);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN7);
    Interrupt_enableMaster();

}

int k = 0;

void PORT4_IRQHandler(void){
    uint16_t flag;
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    GPIO_clearInterruptFlag(GPIO_PORT_P4, flag);
    if(flag & GPIO_PIN6)  //检测到C6被按下
    {
        Clock_Delay1ms(10) ;   //消抖
        if(GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN6) == 0)
        {
            k=0;
            if(C1_flag == 1 & C3_flag == 4)
            {
               if(C8_flag==1)
               {
                   second_zong+=1;
               }
               else if(C8_flag==2)
               {
                   second_zong+=60;
               }
               else if(C8_flag==3)
               {
                   second_zong+=3600;
               }
            }

            if(C1_flag == 1 & C3_flag == 2 ){
                if(C81_flag==1){  //分
                    clocktime[0]=clocktime[0]%60+1;
                    if(clocktime[0] == 60){
                        clocktime[0] = 0;
                    }
                }
                else if (C81_flag==2){  //时
                    clocktime[1]=clocktime[1]%24+1;
                    if(clocktime[1] == 24){
                        clocktime[1] = 0;
                    }
                }
                else if (C81_flag==3){  //周
                    clocktime[2]=clocktime[2]%7+1;
                }
            }

            if(C1_flag == 1 & C3_flag ==0){
                if(C6_flag == 0){
                    C6_flag = 1;
                }
                else if(C6_flag == 1){
                    C6_flag = 2;
                }
                else if(C6_flag == 2){
                    C6_flag = 3;
                }
                else if(C6_flag == 3){
                    C6_flag = 0;
                }
            }
            if(C1_flag == 0 & C61_flag == 0){
                C61_flag = 1;
            }
            else if (C1_flag == 0 & C61_flag == 1){
                C61_flag = 0;
            }
            GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
        }

    }
    if(flag & GPIO_PIN0)  //检测到C1被按下  HOME
    {
        Clock_Delay1ms(10) ;   //消抖
        if(GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN0) == 0)
        {
            k=0;
            if(C1_flag == 0){
                C1_flag = 1;
            }
            else if(C1_flag == 1){
                C1_flag =0;
                C3_flag =0;
                C6_flag =0;
            }
            GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
        }

    }

    if(flag & GPIO_PIN1)  //检测到C3被按下 选择
    {
        Clock_Delay1ms(10) ;   //消抖
        if(GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN1) == 0)
        {
            k=0;
            if(C1_flag == 1 & C6_flag == 0){
                C3_flag =1;
            }
            else if(C1_flag == 1 & C6_flag == 1){
                C3_flag =2;
            }
            else if(C1_flag == 1 & C6_flag == 2){
                C3_flag =3;
            }
            else if(C1_flag == 1 & C6_flag == 3){
                C3_flag =4;
            }


        }
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
    }
    if(flag & GPIO_PIN5)  //检测到C4被按下 选择
        {
            Clock_Delay1ms(10) ;   //消抖
            if(GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN5) == 0)
            {
                k=0;
                C8_flag=0;
                if(C4_flag == 0){
                    if(C3_flag == 4){
                        C4_flag =1;
                        mb=0;
                        C8_flag =0;
                    }
                }
                else{
                    if(C3_flag == 4){
                        C4_flag=0;
                        if(second_zong>0.01*mb){
                        second_zong=second_zong-0.01*mb;}
                        else{
                            second_zong=0;
                        }
                    }
                }
                if(C1_flag == 1 & C3_flag == 2) { //闹钟开启
                    if(C41_flag == 0){
                        C41_flag=1;
                    }
                    else if (C41_flag == 1){
                        C41_flag=0;
                    }
                    C81_flag = 0;
                }

            }
            GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
        }
    if(flag & GPIO_PIN2)  //检测到C5被按下  返回
    {
        Clock_Delay1ms(10) ;   //消抖
        if(GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN2) == 0)
        {
            k=0;
            C3_flag = 0 ;
            if(data_buf[3] == clocktime[1] &data_buf[4] == clocktime[0] &data_buf[6] == clocktime[2]){  //关闭闹钟
                C41_flag= 0;
            }
        }
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
    }
    if(flag & GPIO_PIN7)  //检测到C8被按下
     {
         Clock_Delay1ms(10) ;   //消抖
         if(GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN7) == 0)
         {
             k=0;
             if(C4_flag==0){
                 if(C8_flag == 0 ){
                 C8_flag=1;
             }
                 else if(C8_flag == 1){
                 C8_flag =2;
             }
                 else if(C8_flag == 2){
                 C8_flag=3;
             }
                 else if(C8_flag == 3){
                 C8_flag=0;
             }
         }

             // 闹钟界面更改时间标志位
             if(C1_flag == 1 & C3_flag == 2 ){
                 if(C81_flag == 0 ){
                 C81_flag=1;
             }
                 else if(C81_flag == 1){
                 C81_flag =2;
             }
                 else if(C81_flag == 2){
                 C81_flag=3;
             }
                 else if(C81_flag == 3){
                 C81_flag=0;
             }
             }
         }
         GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
     }
    if(flag & GPIO_PIN3)  //检测到C7被按下
     {
         Clock_Delay1ms(10) ;   //消抖
         if(GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN3) == 0)
         {
             k=0;
             if(C1_flag == 1 & C3_flag == 4)
             {
                if(C8_flag==1&second_zong>=1)
                {
                    second_zong-=1;
                }
                else if(C8_flag==2)
                {
                    if(second_zong>60){
                      second_zong-=60;
                    }
                    else{
                      second_zong=0;
                    }
                }
                else if(C8_flag==3)
                {
                    if(second_zong>3600){
                      second_zong-=3600;
                    }
                    else{
                      second_zong=0;
                    }
                }
             }
         }
         GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
     }
    GPIO_clearInterruptFlag(GPIO_PORT_P4, flag);
}
volatile uint8_t TXData = 49;

void PORT1_IRQHandler(void)    // 中断函数
{

    if(GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN1) == GPIO_PIN1)
    {
        GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
        Clock_Delay1ms(10) ;   //消抖
        if(GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == 0)
        {
            k=0;
            if(C6_flag == 0){
                C6_flag = 1;
            }
            else if(C6_flag == 1){
                C6_flag = 2;
            }
            else if(C6_flag == 2){
                C6_flag = 3;
            }
            else if(C6_flag == 3){
                C6_flag = 0;
            }
            GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
            UART_transmitData(EUSCI_A2_BASE, TXData);
        }

    }
    if(GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN4) == GPIO_PIN4)
    {
        GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
        Clock_Delay1ms(10) ;   //消抖
        if(GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == 0)
        {
            k=0;
            if(C6_flag == 0){
                C6_flag = 1;
            }
            else if(C6_flag == 1){
                C6_flag = 2;
            }
            else if(C6_flag == 2){
                C6_flag = 3;
            }
            else if(C6_flag == 3){
                C6_flag = 0;
            }
            GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
        }

    }
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);

}
