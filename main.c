#include "msp.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include "Clock.h"
#include "Timer32.h"
#include "DS1302.h"
#include "OLED.h"
#include "key.h"
#include "UART0.h"
#include "UART1.h"
#include "interface.h"
#include "Uart.h"

#define  u8 unsigned char
#define  u16 unsigned int
#define  u32 unsigned int

const eUSCI_UART_ConfigV1 uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        78,                                     // BRDIV = 78
        2,                                       // UCxBRF = 2
        0,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
        EUSCI_A_UART_8_BIT_LEN                  // 8 bit data length
};

/**
 * main.c
 */
void main(void)
{
    Clock_Init48MHz();
    OLED_Init();
    UART1_Init();
    Timer32_Init(*get_time,480000,T32DIV1);
    struct ds1302time time_set;
    TIME_SET(&time_set);
    DS1302_write_time(&time_set);
    int data_buf[7];
    key_scan_INTERRUPT();
    uart0_init();
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    while(1)
    {
        data_get(data_buf,data_buf12);
        if (C41_flag == 1){
            if(data_buf[3] == clocktime[1] &data_buf[4] == clocktime[0] &data_buf[6] == clocktime[2]){
                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
            }
        }
        else if(C41_flag == 0){
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
        }
        if(C1_flag == 0){
            HOME();

        }
        else if(C1_flag == 1 & C3_flag ==0){
            Menu();
        }
        else if (C1_flag == 1 & C3_flag == 1 ){

        }
        else if (C1_flag == 1 & C3_flag == 2 ){
            Alarmclock();
        }
        else if (C1_flag == 1 & C3_flag == 3 ){
            Worldtime();
        }
        else if (C1_flag == 1 & C3_flag == 4 ){
            Countdown();
        }

    }

}


