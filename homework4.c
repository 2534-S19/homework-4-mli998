#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework4.h"

int main(void)
{
    char rChar;
    char *response = "\n\n\r2534 is the best course in the curriculum!\r\n\n";

    // TODO: Declare the variables that main uses to interact with your state machine.
    unsigned int uart_temp=0;
    unsigned int c = 0;
    unsigned int USART_RX_STA = 0;

    // Stops the Watchdog timer.
    initBoard();
    // TODO: Declare a UART config struct as defined in uart.h.
    //       To begin, configure the UART for 9600 baud, 8-bit payload (LSB first), no parity, 1 stop bit.
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    const eUSCI_UART_Config uartConfig =
    {
    EUSCI_A_UART_CLOCKSOURCE_SMCLK;
    312;                                   //48000000/9600/16 = 312.5
    8;                                     //0.5*16
    0x00;
    EUSCI_A_UART_NO_PARITY;                 // No Parity
    EUSCI_A_UART_LSB_FIRST;                  // LSB First
    EUSCI_A_UART_ONE_STOP_BIT;              // One stop bit
    EUSCI_A_UART_MODE;                      // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
    };

    // TODO: Make sure Tx AND Rx pins of EUSCI_A0 work for UART and not as regular GPIO pins.
    pin 6 -> P1.2/UCA0RXD/UCA0SOMI;
    pin 7 -> P1.3/UCA0TXD/UCA0SIMO;
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,GPIO_PIN2,GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,GPIO_PIN3,GPIO_PRIMARY_MODULE_FUNCTION);

    // TODO: Initialize EUSCI_A0

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    UART_initModule(EUSCI_A0_BASE, &uartConfig);

    // TODO: Enable EUSCI_A0

    UART_enableModule(EUSCI_A0_BASE);
    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableMaster();


    while(1)
    {
        // TODO: Check the receive interrupt flag to see if a received character is available.
        //       Return 0xFF if no character is available.
        if(Res!=0x0a)
        {
            USART_RX_STA=0;
        }
        else
        {
            USART_RX_STA|=0xFF;
        }

        // TODO: If an actual character was received, echo the character to the terminal AND use it to update the FSM.
        //       Check the transmit interrupt flag prior to transmitting the character.
        uart_temp++;
        uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
        UART_clearInterruptFlag(EUSCI_A0_BASE, status);
        if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
        {
            // Throw away received data
            UART_receiveData(EUSCI_A0_BASE);
        }
        if (status & EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
        {
            // Transmit the next byte here
            EUSCI_A_UART_transmitData(EUSCI_A0_BASE, 'H');
            uart_temp=0;
        }

        // TODO: If the FSM indicates a successful string entry, transmit the response string.
        //       Check the transmit interrupt flag prior to transmitting each character and moving on to the next one.
        //       Make sure to reset the success variable after transmission.

        char uart_get_key(void)
        {
           if(rUTRSTAT0 &0x1)
            return  RdURXH0();
            else
            return 0;
        }

        char *string2 = string;
        char c;
        while((c = uart_get_key())!='/r')
        {
            if(c == '/b')
            {
                if((int)string2 < (int)string)
                {
                    string --;
                }
            }
            else
            {
                *string++ = c;
            }
        }
        *string = '/0';
    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// TODO: FSM for detecting character sequence.
bool charFSM(char rChar)
{
    char c;
    while (1)
    {
        if (UARTHasChar()) {
            c = read_uart_char();
            process_char(c);  // an FSM
     }

}
