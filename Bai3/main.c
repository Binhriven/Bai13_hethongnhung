#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x_usart.h"
#include "semphr.h"

void uart_init(uint32_t baudrate);
void uart_send_char(char c);
void uart_send_string(const char *str);
void taskA(void *pvParameters);
void taskB(void *pvParameters);

SemaphoreHandle_t uartMutex;

int main(void)
{
    SystemInit();
    uart_init(9600);

    uartMutex = xSemaphoreCreateMutex();

    xTaskCreate(taskA, "TASKA", 128, NULL, 1, NULL);
    xTaskCreate(taskB, "TASKB", 128, NULL, 1, NULL);

    vTaskStartScheduler();
    
    while(1);
}

void uart_init(uint32_t baudrate)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpio;
    USART_InitTypeDef uart;

    // PA9 - TX
    gpio.GPIO_Pin = GPIO_Pin_9;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    // PA10 - RX
    gpio.GPIO_Pin = GPIO_Pin_10;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio);

    uart.USART_BaudRate = baudrate;
    uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    uart.USART_Parity = USART_Parity_No;
    uart.USART_StopBits = USART_StopBits_1;
    uart.USART_WordLength = USART_WordLength_8b;

    USART_Init(USART1, &uart);
    USART_Cmd(USART1, ENABLE);
}

void uart_send_char(char c)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, (uint16_t)c);
}

void uart_send_string(const char *str)
{
    while(*str) uart_send_char(*str++);
}

void taskA(void *pvParameters)
{
    const char *s1 = "HELLO BINH\r\n";

    while(1)
    {
        /* Chi?m quy?n UART */
        if(xSemaphoreTake(uartMutex, portMAX_DELAY) == pdTRUE)
        {
            uart_send_string(s1);
            xSemaphoreGive(uartMutex); // Tr? mutex l?i
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void taskB(void *pvParameters)
{
    const char *s2 = "hello binh\r\n";

    while(1)
    {
        if(xSemaphoreTake(uartMutex, portMAX_DELAY) == pdTRUE)
        {
            uart_send_string(s2);
            xSemaphoreGive(uartMutex);
        }

        vTaskDelay(pdMS_TO_TICKS(150));
    }
}
