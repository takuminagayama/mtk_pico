/*
 * GPIO Example for Raspberry Pi Pico
 * Demonstrates how to control GPIO pins with voltage output
 */

#include <stdint.h>
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include <bsp/libbsp.h>

/*
 * RP2040 GPIO Register Definitions
 * Reference: RP2040 Datasheet Section 2.19
 */

/* GPIO Register Base Addresses */
#define GPIO_BASE       0x40014000
#define PADS_BANK0_BASE 0x4001c000
#define IO_BANK0_BASE   0x40014000

/* GPIO Register Offsets */
#define GPIO_OE_OFFSET  0x20    /* Output Enable */
#define GPIO_OUT_OFFSET 0x10    /* Output Value */

/* GPIO Control Register Offsets */
#define GPIO_CTRL_OFFSET 0x04

/* Pad Control Register Offsets */
#define PADS_OE_OFFSET  0x06

/* SIO (Single-cycle I/O) Base */
#define SIO_BASE        0xd0000000
#define SIO_GPIO_OUT    (SIO_BASE + 0x10)
#define SIO_GPIO_SET    (SIO_BASE + 0x14)
#define SIO_GPIO_CLR    (SIO_BASE + 0x18)
#define SIO_GPIO_OE     (SIO_BASE + 0x20)
#define SIO_GPIO_OE_SET (SIO_BASE + 0x24)
#define SIO_GPIO_OE_CLR (SIO_BASE + 0x28)

/* Helper macros for register access */
#define REG_RD(addr)        (*(volatile uint32_t *)(addr))
#define REG_WR(addr, val)   (*(volatile uint32_t *)(addr)) = (val)
#define REG_SET(addr, val)  (*(volatile uint32_t *)(addr)) |= (val)
#define REG_CLR(addr, val)  (*(volatile uint32_t *)(addr)) &= ~(val)

/**
 * gpio_init - Initialize a GPIO pin as output
 * @pin: GPIO pin number (0-29)
 */
void gpio_init(uint8_t pin)
{
	if (pin >= 30) return;  /* Invalid pin */
	
	/* Set GPIO pin as output using SIO */
	REG_SET(SIO_GPIO_OE, (1u << pin));
	
	tm_printf((UB*)"GPIO pin %d initialized as output\n", pin);
}

/**
 * gpio_set - Set GPIO pin to HIGH (3.3V)
 * @pin: GPIO pin number (0-29)
 */
void gpio_set(uint8_t pin)
{
	if (pin >= 30) return;
	REG_WR(SIO_GPIO_SET, (1u << pin));
}

/**
 * gpio_clr - Set GPIO pin to LOW (0V)
 * @pin: GPIO pin number (0-29)
 */
void gpio_clr(uint8_t pin)
{
	if (pin >= 30) return;
	REG_WR(SIO_GPIO_CLR, (1u << pin));
}

/**
 * gpio_toggle - Toggle GPIO pin state
 * @pin: GPIO pin number (0-29)
 */
void gpio_toggle(uint8_t pin)
{
	if (pin >= 30) return;
	
	uint32_t current = REG_RD(SIO_GPIO_OUT);
	if (current & (1u << pin)) {
		gpio_clr(pin);
	} else {
		gpio_set(pin);
	}
}

/**
 * gpio_read - Read GPIO pin state
 * @pin: GPIO pin number (0-29)
 * @return: 1 if HIGH, 0 if LOW
 */
uint8_t gpio_read(uint8_t pin)
{
	if (pin >= 30) return 0;
	
	uint32_t val = REG_RD(SIO_GPIO_OUT);
	return (val >> pin) & 1;
}

/* Example usage functions */

/**
 * Example 1: Simple LED blink on GPIO 25 (on-board LED)
 */
void example_led_blink(void)
{
	gpio_init(25);
	
	while(1) {
		gpio_set(25);    /* LED ON (3.3V) */
		tm_printf((UB*)"LED ON\n");
		tk_dly_tsk(500);
		
		gpio_clr(25);    /* LED OFF (0V) */
		tm_printf((UB*)"LED OFF\n");
		tk_dly_tsk(500);
	}
}

/**
 * Example 2: Multiple GPIO control (GPIO 0, 1, 2)
 */
void example_multiple_pins(void)
{
	uint8_t pins[] = {0, 1, 2};
	int i;
	
	/* Initialize all pins */
	for (i = 0; i < 3; i++) {
		gpio_init(pins[i]);
	}
	
	/* Sequentially control pins */
	while(1) {
		for (i = 0; i < 3; i++) {
			gpio_set(pins[i]);
			tm_printf((UB*)"GPIO%d set to 3.3V\n", pins[i]);
			tk_dly_tsk(300);
			
			gpio_clr(pins[i]);
			tm_printf((UB*)"GPIO%d set to 0V\n", pins[i]);
			tk_dly_tsk(300);
		}
	}
}

/**
 * Example 3: PWM-like effect using software toggling
 */
void example_pwm_effect(void)
{
	gpio_init(15);  /* GPIO15 for PWM simulation */
	
	while(1) {
		/* 75% duty cycle */
		gpio_set(15);
		tk_dly_tsk(75);   /* ON for 75ms */
		
		gpio_clr(15);
		tk_dly_tsk(25);   /* OFF for 25ms */
	}
}

/**
 * Example 4: Output voltage sweep (controlled via register writes)
 */
void example_voltage_control(void)
{
	uint8_t pin = 18;
	gpio_init(pin);
	
	tm_printf((UB*)"GPIO%d voltage control example\n", pin);
	
	while(1) {
		/* Set pin to 3.3V */
		gpio_set(pin);
		tm_printf((UB*)"GPIO%d = 3.3V (HIGH)\n", pin);
		tk_dly_tsk(1000);
		
		/* Set pin to 0V */
		gpio_clr(pin);
		tm_printf((UB*)"GPIO%d = 0V (LOW)\n", pin);
		tk_dly_tsk(1000);
	}
}

/**
 * Initialization function to call from main
 */
void gpio_example_init(void)
{
	tm_printf((UB*)"GPIO Example initialized\n");
	tm_printf((UB*)"GPIO pins can be controlled to output 3.3V or 0V\n");
	
	/* Uncomment the example you want to run */
	/* example_led_blink(); */
	/* example_multiple_pins(); */
	/* example_pwm_effect(); */
	/* example_voltage_control(); */
}
