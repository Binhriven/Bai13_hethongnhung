#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define LED_BLINK_PIN GPIO_Pin_5
#define LED_ALERT_PIN GPIO_Pin_6
#define LED_PORT GPIOA

#define BUTTON_PIN GPIO_Pin_13
#define BUTTON_PORT GPIOC

QueueHandle_t xAlertQueue;
SemaphoreHandle_t xAlertSemaphore;
TaskHandle_t xAlertTaskHandle;

void GPIO_Config(void);
void EXTI_Config(void);
void NVIC_Config(void);
void vLEDBlinkTask(void *pvParameters);
void vAlertTask(void *pvParameters);

int main(void)
{
    SystemInit();
    GPIO_Config();
    EXTI_Config();
    NVIC_Config();
    
    xAlertQueue = xQueueCreate(5, sizeof(uint8_t));
    xAlertSemaphore = xSemaphoreCreateBinary();
    
    xTaskCreate(vLEDBlinkTask, "LED Blink", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vAlertTask, "Alert Task", configMINIMAL_STACK_SIZE, NULL, 3, &xAlertTaskHandle);
    
    vTaskStartScheduler();
    
    while(1);
}

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = LED_BLINK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = LED_ALERT_PIN;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = BUTTON_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(BUTTON_PORT, &GPIO_InitStructure);
    
    GPIO_ResetBits(LED_PORT, LED_BLINK_PIN);  
    GPIO_ResetBits(LED_PORT, LED_ALERT_PIN);  
}

void EXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void vLEDBlinkTask(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 1000; // 1000ms
    
    xLastWakeTime = xTaskGetTickCount();
    
    while(1)
    {
        GPIO_WriteBit(LED_PORT, LED_BLINK_PIN, 
                     (BitAction)(1 - GPIO_ReadOutputDataBit(LED_PORT, LED_BLINK_PIN)));
        
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void vAlertTask(void *pvParameters)
{
    uint8_t alertCommand;
    
    while(1)
    {
        if(xSemaphoreTake(xAlertSemaphore, portMAX_DELAY) == pdTRUE)
        {
            if(xQueueReceive(xAlertQueue, &alertCommand, 0) == pdTRUE)
            {

                GPIO_SetBits(LED_PORT, LED_ALERT_PIN);
                
                vTaskDelay(pdMS_TO_TICKS(2000));
                
                GPIO_ResetBits(LED_PORT, LED_ALERT_PIN);
            }
        }
    }
}

void EXTI15_10_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint8_t alertCmd = 1;
    
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        for(volatile int i = 0; i < 1000; i++);
        
        if(GPIO_ReadInputDataBit(BUTTON_PORT, BUTTON_PIN) == 0)
        {
            xQueueSendToBackFromISR(xAlertQueue, &alertCmd, &xHigherPriorityTaskWoken);
            xSemaphoreGiveFromISR(xAlertSemaphore, &xHigherPriorityTaskWoken);
        }
        
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
    
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
