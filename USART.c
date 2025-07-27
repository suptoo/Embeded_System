// Note: The original image used '#import', which is non-standard.
// Standard C uses '#include' for header files.
#include "stm32f10x.h"

/**
 * @brief Initializes the UART1 peripheral and corresponding GPIO pins.
 */
void UART_Init(void) {
    // Enable clock for GPIOA (for TX/RX pins) and UART1
    RCC->APB2ENR |= (1 << 2);  // Enable GPIOA clock
    RCC->APB2ENR |= (1 << 14); // Enable USART1 clock

    // Configure GPIOA pins for UART
    // PA9 (TX) as Alternate function push-pull
    // PA10 (RX) as Floating input
    GPIOA->CRH &= ~(255 << 4); // Clear settings for PA9 and PA10
    GPIOA->CRH |= (11 << 4);  // PA9: AF-PP, 50MHz
    GPIOA->CRH |= (4 << 8);   // PA10: Floating Input

    // Configure USART1 Baud Rate (assuming a specific system clock, e.g., 72MHz)
    // For 9600 baud with PCLK2 at 72MHz, BRR value is 468.75
    // Mantissa = 468, Fraction = 0.75 * 16 = 12
    USART1->BRR = (468 << 4);
    USART1->BRR |= 12;

    // Enable UART Transmitter and Receiver
    USART1->CR1 |= (1 << 13); // Enable USART1
    USART1->CR1 |= (1 << 3);  // Enable Transmitter (TE)
    USART1->CR1 |= (1 << 2);  // Enable Receiver (RE)
}

/**
 * @brief Waits for and receives a single character from UART1.
 * @return The received character.
 */
char UART_ReceiveChar(void) {
    // Wait until the Receive Data Register Not Empty (RXNE) flag is set
    while (!(USART1->SR & (1 << 5)));
    return USART1->DR;
}

/**
 * @brief Sends a single character via UART1.
 * @param c The character to send.
 */
void UART_SendChar(char c) {
    // Wait until the Transmit Data Register Empty (TXE) flag is set
    while (!(USART1->SR & (1 << 7)));
    USART1->DR = c;
}

/**
 * @brief Main program loop. Initializes UART and echoes received characters.
 */
int main(void) {
    UART_Init();

    while (1) {
        // Wait to receive a character
        char c = UART_ReceiveChar();
        // Send the same character back (echo)
        UART_SendChar(c);
    }
}
