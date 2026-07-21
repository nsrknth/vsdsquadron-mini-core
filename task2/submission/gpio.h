#ifndef TASK2_GPIO_H
#define TASK2_GPIO_H

/*
 * Task 2 GPIO API
 *
 * This interface hides board-specific registers and SDK calls from main.c.
 * It controls the onboard blue user LED L1, mapped by the board datasheet to
 * firmware GPIO PD6.
 */
void gpio_init(void);
void gpio_set(void);
void gpio_clear(void);

#endif
