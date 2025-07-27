// Include STM32F10x peripheral library header file
#include "stm32f10x.h"

// Function prototypes
void  delay_ms(uint32_t ms);    // Function to create millisecond delay
void gpio_init(void);           // Function to initialize GPIO pins
void adc_init(void);            // Function to initialize ADC peripheral
uint16_t adc_read(void);        // Function to read ADC value
// GPIO initialization function
void gpio_init(void)
{
    RCC->APB2ENR|=(1<<4);       // Enable GPIOC clock by setting bit 4 in APB2ENR register
    GPIOC->CRH &=~(0xF<<20);    // Clear PC13 configuration bits (bits 23-20)
    GPIOC->CRH |= (0x3<<20);    // Configure PC13 as output push-pull, max speed 50MHz
    RCC->APB2ENR |= (1<<2);     // Enable GPIOA clock by setting bit 2 in APB2ENR register
    GPIOA->CRL &= ~(0xF<<0);    // Clear PA0 configuration bits (bits 3-0)
    GPIOA->CRL |= (0x0<<0);     // Configure PA0 as analog input (ADC input)
}
// ADC initialization function
void adc_init(void)
{
    RCC->APB2ENR |= (1<<9);         // Enable ADC1 clock by setting bit 9 in APB2ENR register
    ADC1->CR2 |=(1<<0);             // Enable ADC1 by setting ADON bit in CR2 register
    for(volatile int i = 0; i < 1000; i++); // Small delay to allow ADC to stabilize
    ADC1->SMPR2 |= (0x7<<0);        // Set sampling time for channel 0 to 239.5 cycles (maximum sampling time)
}
// ADC read function - reads analog value from channel 0 (PA0)
uint16_t adc_read(void)
{
    ADC1->SQR1 = (1-1)<<20;         // Set sequence length to 1 conversion (L[3:0] = 0)
    ADC1->SQR3 = (0<<0);            // Set first conversion in sequence to channel 0 (PA0)
    ADC1->CR2 |= (1<<0);            // Start ADC conversion by setting ADON bit
    while(!(ADC1->SR & (1<<1)));    // Wait for conversion to complete (EOC flag)
    return ADC1->DR;                // Return the converted digital value (12-bit: 0-4095)
}
// Delay function - creates approximate millisecond delay
void delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms * 8000; i++); // Loop approximately 8000 times per millisecond
}
// Main function - program entry point
int main(void)
{
    gpio_init();                    // Initialize GPIO pins (PC13 as output, PA0 as ADC input)
    adc_init();                     // Initialize ADC1 peripheral
    
    while(1)                        // Infinite loop - main program execution
    {
        uint16_t adc_value = adc_read();            // Read ADC value from PA0 (0-4095 range)
        uint32_t delay=100+(adc_value*900)/4095;    // Calculate delay: 100ms + (0-900ms based on ADC value)
        GPIOC->ODR ^=(1<<13);                       // Toggle PC13 (LED) by XORing bit 13 in ODR register
        delay_ms(delay);                            // Wait for calculated delay period
    }
} 