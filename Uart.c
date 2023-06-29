#include "msp.h"
#include "key.h"
#include "Clock.h"
#include "DS1302.h"
#include "OLED.h"
#include "interface.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "Uart.h"
#include <stdint.h>
#include <stdbool.h>

const eUSCI_UART_ConfigV1 uartconfig =
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



void uart0_init(void){

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    UART_initModule(EUSCI_A2_BASE,&uartconfig);
    UART_enableModule(EUSCI_A2_BASE);
    UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);

    Interrupt_enableInterrupt(INT_EUSCIA2);
//    Interrupt_enableSleepOnIsrExit();

}

void EUSCIA0_IRQHandler(void){

    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
    uint8_t recieve;
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        recieve = UART_receiveData(EUSCI_A2_BASE);
        UART_transmitData(EUSCI_A2_BASE, recieve);
    }
    UART_clearInterruptFlag(EUSCI_A2_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);
}








