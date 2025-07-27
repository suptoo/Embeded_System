// This program detects a button press on PC15 and toggles an LED on PB0.

#include <stdint.h> // It's good practice to include this for types like uint8_t

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)
#define GPIOB_CRL   (*(volatile uint32_t *)0x40010C00)
#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004)
#define GPIOB_ODR   (*(volatile uint32_t *)0x40010C0C)
#define GPIOC_IDR   (*(volatile uint32_t *)0x40011008)

void delay(uint32_t count) {
	for(uint32_t i = 0; i < count; ++i) {
        // This is a simple busy-wait loop. The __NOP() intrinsic is often used here
        // in real applications to prevent the loop from being optimized away.
	}
}

void setup() {
	// Enable clocks for GPIOB and GPIOC
	RCC_APB2ENR |= (1<<3); // GPIOB
	RCC_APB2ENR |= (1<<4); // GPIOC

	// Set PB0 as output (push-pull, max speed 50 MHz)
    // Mode 0011 -> 0x3
	GPIOB_CRL &= ~(15UL<<0);
	GPIOB_CRL |= 3UL<<0;

	// Set PC15 as input with pull-up / pull-down
    // Mode 0100 -> 0x4
	GPIOC_CRH &= ~(15UL<<28);
	GPIOC_CRH |= 4UL<<28;
}

uint8_t debounce(uint8_t last) {
    uint8_t current = (GPIOC_IDR & (1<<15)) ? 1 : 0;
    if (last != current) {
        delay(50000); // Simple delay for debouncing
        current = (GPIOC_IDR & (1<<15)) ? 1 : 0;
    }
    return current;
}

int main_program1() { // Renamed to avoid conflict with Program 2's main
    uint8_t lastButton = 0;
    uint8_t currentButton = 0;
    uint8_t ledOn = 0;

    setup();

    while (1) {
        currentButton = debounce(lastButton);
        if (lastButton == 0 && currentButton == 1) { // Detect rising edge
            ledOn = !ledOn;
        }
        lastButton = currentButton;

        if (ledOn) {
            GPIOB_ODR |= (1<<0); // Turn LED on
        } else {
            GPIOB_ODR &= ~(1<<0); // Turn LED off
        }
    }
    // return 0; // Unreachable code in embedded systems
}
