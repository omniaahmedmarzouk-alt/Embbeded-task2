#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

#define GPIO_INPUT  1
#define GPIO_OUTPUT 0
#define GPIO_HIGH   1
#define GPIO_LOW    0

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3
#define PORT_E 4

typedef struct {
    uint8_t port;
    uint8_t pin;
    uint8_t direction;
    uint8_t initial_state;
} GPIO_PinConfig;

static volatile uint8_t* const TRIS_REGS[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
static volatile uint8_t* const PORT_REGS[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

void GPIO_PinInit(GPIO_PinConfig *config);
void GPIO_WritePin(GPIO_PinConfig *config, uint8_t value);
uint8_t GPIO_ReadPin(GPIO_PinConfig *config);
void GPIO_TogglePin(GPIO_PinConfig *config);

#endif