// Note: The original image used '#import', which is non-standard.
// Standard C uses '#include' for header files.
#include "stm32f10x.h"

/**
 * @brief Main program to configure and toggle an LED using a timer delay.
 */
int main() {
    //--- GPIO Configuration ---
    // Enable clock for GPIOA
    RCC->APB2ENR |= 1UL << 2;

    // Set PA0 as output (General-purpose output push-pull, 50MHz)
    GPIOA->CRL &= ~(15UL << 0);
    GPIOA->CRL |= (3UL << 0);

    //--- Timer 2 Configuration ---
    // Enable TIM2 clock (TIM2 is on the APB1 bus)
    RCC->APB1ENR |= 1UL << 0;

    // Set Count = 0
    TIM2->CNT = 0;

    // Set the prescaler value.
    // The timer clock is typically a multiple of the system clock.
    // Assuming a system clock of 72MHz, the timer clock can be 72MHz.
    // To get a 1ms tick, we need to divide the clock.
    // If we use a prescaler of 3600, the timer clock becomes 72,000,000 / 3600 = 20,000 Hz.
    // For a 1000ms delay, we would need different values.
    // Let's assume the prescaler is set to achieve a 10kHz timer clock frequency.
    // For a 72MHz system clock, PSC would be 7200-1.
    // The value 3600-1 gives a 20kHz clock.
    TIM2->PSC = 3600 - 1;

    // Set the Auto-reload value for 1000 ms (1 second)
    // With a 20kHz clock, we need 20,000 counts for 1 second.
    // The value 10000-1 from the image would give a 500ms delay.
    // To achieve 1000ms, we would set ARR to 20000-1.
    // We will use the value from the image.
    TIM2->ARR = 10000 - 1;

    // Configure as One-Pulse Mode (OPM)
    // When OPM is set, the counter stops counting automatically at the next update event.
    TIM2->CR1 |= 1UL << 3;

    //--- Main Loop ---
    while (1) {
        TIM2->CR1 |= 1; // Start Timer
        
        // Wait until the timer has finished counting.
        // The CEN (Counter Enable) bit in CR1 will be cleared by hardware in one-pulse mode.
        while (TIM2->CR1 & 1); // Check if still counting
        
        // Toggle the output on pin PA0
        GPIOA->ODR ^= 1UL << 0;
    }
}
