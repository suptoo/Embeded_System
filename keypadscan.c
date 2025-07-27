
#include <stdint.h>
#include <stddef.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)
#define GPIOA_CRL   (*(volatile uint32_t *)0x40010800)
#define GPIOA_IDR   (*(volatile uint32_t *)0x40010808)
#define GPIOA_ODR   (*(volatile uint32_t *)0x4001080C)

int row, col;

unsigned char key_map[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'},
};

char input_string[100] = {0};
int input_index = 0;

void enable_clock() {
    RCC_APB2ENR |= 1UL << 2;
}

void add_to_string(char c) {
    if (input_index < (sizeof(input_string) - 1)) {
        input_string[input_index] = c;
        input_index++;
        input_string[input_index] = '\0';
    }
}

void set_output_pins() {
    GPIOA_CRL &= ~(15UL << 0);
    GPIOA_CRL |= (3UL << 0);

    GPIOA_CRL &= ~(15UL << 4);
    GPIOA_CRL |= (3UL << 4);

    GPIOA_CRL &= ~(15UL << 8);
    GPIOA_CRL |= (3UL << 8);

    GPIOA_CRL &= ~(15UL << 12);
    GPIOA_CRL |= (3UL << 12);
}

void set_input_pins() {
    GPIOA_CRL &= ~(15UL << 16);
    GPIOA_CRL |= (4UL << 16);

    GPIOA_CRL &= ~(15UL << 20);
    GPIOA_CRL |= (4UL << 20);

    GPIOA_CRL &= ~(15UL << 24);
    GPIOA_CRL |= (4UL << 24);
}

void get_column() {
    if ((GPIOA_IDR & (1UL << 4)) == 0) {
        col = 0;
    }
    else if ((GPIOA_IDR & (1UL << 5)) == 0) {
        col = 1;
    }
    else if ((GPIOA_IDR & (1UL << 6)) == 0) {
        col = 2;
    }
    else {
        col = -1;
    }
}

void get_row() {
    GPIOA_ODR &= ~(15UL << 0);
    GPIOA_ODR |= (14UL << 0);
    if ((GPIOA_IDR & (7UL << 4)) != 112) { row = 0; }

    GPIOA_ODR &= ~(15UL << 0);
    GPIOA_ODR |= (13UL << 0);
    if ((GPIOA_IDR & (7UL << 4)) != 112) { row = 1; }

    GPIOA_ODR &= ~(15UL << 0);
    GPIOA_ODR |= (11UL << 0);
    if ((GPIOA_IDR & (7UL << 4)) != 112) { row = 2; }

    GPIOA_ODR &= ~(15UL << 0);
    GPIOA_ODR |= (7UL << 0);
    if ((GPIOA_IDR & (7UL << 4)) != 112) { row = 3; }
}

int main() {
    enable_clock();
    set_output_pins();
    set_input_pins();

    while (1) {
        get_column();
        if (col == -1) {
            continue;
        }
        
        get_row();
        
        add_to_string(key_map[row][col]);
    }
}
