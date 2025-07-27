// This program has the same functionality as Program 1 but uses the
// standard device header file for register access.

#include "stm32f10x.h" // Device header

void delay_p2(uint32_t count) { // Renamed to avoid conflict
	for(uint32_t i = 0; i < count; ++i) {
        // NOP
	}
}

void setup_p2() { // Renamed to avoid conflict
    // Enable clocks for GPIOB and GPIOC
	RCC->APB2ENR |= (1<<3); // GPIOB
	RCC->APB2ENR |= (1<<4); // GPIOC

	// Set PB0 as output (push-pull, max speed 50 MHz)
	GPIOB->CRL &= ~(15UL<<0);
	GPIOB->CRL |= 3UL<<0;

	// Set PC15 as input
	GPIOC->CRH &= ~(15UL<<28);
	GPIOC->CRH |= 4UL<<28;
}

uint8_t debounce_p2(uint8_t last) { // Renamed to avoid conflict
    uint8_t current = (GPIOC->IDR & (1<<15)) ? 1 : 0;
    if (last != current) {
        delay_p2(50000);
        current = (GPIOC->IDR & (1<<15)) ? 1 : 0;
    }
    return current;
}

int main() {
    uint8_t lastButton = 0;
    uint8_t currentButton = 0;
    uint8_t ledOn = 0;

    setup_p2();

    while (1) {
        currentButton = debounce_p2(lastButton);
        if (lastButton == 0 && currentButton == 1) {
            ledOn = !ledOn;
        }
        lastButton = currentButton;
        
        if (ledOn) {
            GPIOB->ODR |= (1<<0);
        } else {
            GPIOB->ODR &= ~(1<<0);
        }
    }
    // return 0; // Unreachable
}
