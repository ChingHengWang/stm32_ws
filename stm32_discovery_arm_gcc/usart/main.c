
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


int i;
 
void My_Usart3_Printf(char *string){
    while(*string){
        /* 傳送訊息至 USART3 */
        USART_SendData(USART3, (unsigned short int) *string++);
 
        /* 等待訊息傳送完畢 */
        while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
    }
}
 
int main(void){
    /******** 宣告 USART、GPIO 結構體 ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
 
    /******** 啟用 GPIOC、USART3 的 RCC 時鐘 ********/
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  
      /******** 將 PC10、PC11 連接至 USART3 ********/
      GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
      GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
 
      /******** 設定 PC10 為 Tx 覆用  ********/
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 使用上拉電阻
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // 設定第 10 腳
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
      GPIO_Init(GPIOC, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOC
 
      /******** 設定 PC11 為 Rx 覆用  ********/
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // 設定第 11 腳
      GPIO_Init(GPIOC, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOC
 
      /******** USART 基本參數設定 ********/
      USART_InitStructure.USART_BaudRate = 9600; // 設定 USART 包率 (每秒位元數) 為 9600
      USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
      USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
      USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
      USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
      USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
      USART_Init(USART3, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART3
    
      /******** 啟用 USART3 ********/
      USART_Cmd(USART3, ENABLE);
 
      while (1){
          My_Usart3_Printf("Hello !!\r\n"); // 傳送字串至 USART3
          for(i=0; i<30000000; i++); // 延遲
      }
}
 

