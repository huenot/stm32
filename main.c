#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void delay(unsigned int nCount);
GPIO_InitTypeDef GPIO_InitStruct;

int main (void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_SetBits(GPIOA, GPIO_Pin_0);

    int pwr = 1; // pidr
    int cls = 1;
    int mor = 1;
    while (1)
    {
        for (int i = 0; i < 8; i++){
            int d = 1 << i;
            int is = (pwr & d) == d;
            if (is)
                GPIO_SetBits(GPIOA, GPIO_Pin_0);
            else
                GPIO_ResetBits(GPIOA, GPIO_Pin_0);
            delay(d);
        }
        cls++;
        if (cls > 10){
            cls = 0;
            if (mor)
                pwr++;
            else
                pwr--;

            if (pwr > 255)
            {
                pwr = 255;
                mor = 0;
            }
            if (pwr < 0)
            {
                pwr = 0;
                mor = 1;
            }

        }
    }
}

void delay(unsigned int nCount)
{
    unsigned int i, j;

    for (i = 0; i < nCount; i++)
        for (j = 0; j < 0x0100; j++);
}
