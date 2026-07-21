#include <ch32v00x.h>
#include <debug.h>
#include "gpio.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void Delay_Init(void);
void Delay_Ms(uint32_t n);

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	SystemCoreClockUpdate();
	Delay_Init();
	gpio_init();

	USART_Printf_Init(115200);
	Delay_Ms(1000); 
	
	/* Task 2 startup message: board name and firmware version. */
	printf("\r\n=== VSDSquadron Mini boot ===\r\n");
	printf("Firmware version: 1.0.0\r\n");

	uint32_t counter = 0;

	while (1) {
		/*
		 * Task 2 GPIO proof: toggle the onboard blue L1 LED once per second.
		 * main.c uses only the GPIO API; hardware details stay in gpio.c.
		 */
		if ((counter & 1U) == 0U) {
			gpio_set();
		}
		else {
			gpio_clear();
		}

		/* Task 2 UART proof: capture at least 10 consecutive lines. */
		printf("VSDSquadron Mini | FW 1.0.0 | Counter: %lu\r\n", (unsigned long)counter);

		counter++;
		Delay_Ms(1000);
	}
}

void NMI_Handler(void) {}
void HardFault_Handler(void) {
	while (1) { }
}
