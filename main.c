#include "stm32f10x.h"
#include "platform_config.h"
uint32_t Count;

void GPIO_Configuration(void);
void Delay(__IO uint32_t nCount);

//int main(void)
{
  BoardInit();  // Configure board specific setting
  GPIO_Configuration();  /* GPIO Configuration*/
  while (1)  /* Toggle LED */
    {
      //Check the state of OB_SW
      if (OB_SW_IS_PRESSED)        Count = 0xFFFFF;
      else        Count = 0x1FFFF;

      GPIO_SetBits(OB_LED_PORT, OB_LED_PIN);      /* Turn on LED */
      Delay(Count);      /* Insert delay */
      GPIO_ResetBits(OB_LED_PORT, OB_LED_PIN);      /* Turn off LED */
      Delay(Count);      /* Insert delay */
    }
}

void GPIO_Configuration(void)
{
  //Supply APB2 Clock
  RCC_APB2PeriphClockCmd(OB_LED_GPIO_RCC | OB_SW_GPIO_RCC , ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure OB_LED: output push-pull */
  GPIO_InitStructure.GPIO_Pin = OB_LED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(OB_LED_PORT, &GPIO_InitStructure);

  /* Configure OB_SW: input floating */
  GPIO_InitStructure.GPIO_Pin = OB_SW_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(OB_SW_PORT, &GPIO_InitStructure);

}

void Delay(__IO uint32_t nCount){  for(; nCount != 0; nCount--);  }
