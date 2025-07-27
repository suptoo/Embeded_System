//C Code to Light LED on PA5
#include <stdint.h>

#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800

#define APB2ENR_OFFSET 0x18
#define GPIOA_CRL_OFFSET 0x00
#define GPIOA_ODR_OFFSET 0x0C

#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + APB2ENR_OFFSET))
#define GPIOA_CRL (*(volatile uint32_t *)(GPIOA_BASE + GPIOA_CRL_OFFSET))
#define GPIOA_ODR (*(volatile uint32_t *)(GPIOA_BASE + GPIOA_ODR_OFFSET))

void GPIO_Clock_Enable(void);
void GPIO_Pin_Init(void);

void GPIO_Clock_Enable(void) {
    RCC_APB2ENR |= 1UL << 2;
}

void GPIO_Pin_Init(void) {
    GPIOA_CRL &= ~(15UL << 20);
    GPIOA_CRL |= 3UL << 20;
}

int main(void) {
    GPIO_Clock_Enable();
    GPIO_Pin_Init();
    GPIOA_ODR |= 1UL << 5;

    while (1) {
    }

    return 0;
}