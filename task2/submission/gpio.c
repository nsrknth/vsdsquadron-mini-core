#include <ch32v00x.h>

#include "gpio.h"

/* Datasheet mapping: onboard blue user LED L1 -> port D, pin 6 (PD6). */
#define USER_LED_PORT GPIOD
#define USER_LED_PIN GPIO_Pin_6

void gpio_init(void) {
	GPIO_InitTypeDef config = {0};

	/* BLINKY_CLOCK_ENABLE */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	// GPIO_ResetBits(USER_LED_PORT, USER_LED_PIN); 
	config.GPIO_Pin = USER_LED_PIN;
	config.GPIO_Mode = GPIO_Mode_Out_PP;
	config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USER_LED_PORT, &config);
}

void gpio_set(void) {
	GPIO_SetBits(USER_LED_PORT, USER_LED_PIN);
}

void gpio_clear(void) {
	GPIO_ResetBits(USER_LED_PORT, USER_LED_PIN);
}
