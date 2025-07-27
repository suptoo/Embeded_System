#include "stm32f10x.h"

void GPIO_Clock_Enable(void);
void GPIO_Pin_Init(void);

void GPIO_Clock_Enable(void) {
    RCC->APB2ENR |= 1UL << 2;
}

void GPIO_Pin_Init(void) {
    GPIOA->CRL &= ~(15UL << 20);
    GPIOA->CRL |= 3UL << 20;
}

int main(void) {
    GPIO_Clock_Enable();
    GPIO_Pin_Init();

    GPIOA->ODR |= 1UL << 5;

    while (1) {
    }
}
