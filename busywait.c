// Polling/Busy-Wait Example
while (1) {
    // Toggle red LED when button PA.0 is pushed
    if((GPIOA->IDR & 0x1) == 0x1){
        GPIOB->ODR ^= GPIO_ODR_ODR_2; // Toggle pin PB.2
        while((GPIOA->IDR & 0x1) != 0x00); // Wait until button is released
    }
}
