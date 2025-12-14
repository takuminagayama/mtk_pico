/*
 * GPIO Control Header for Raspberry Pi Pico
 */

#ifndef GPIO_EXAMPLE_H
#define GPIO_EXAMPLE_H

#include <stdint.h>

/**
 * GPIO Pin Definitions (RP2040)
 * Pins 0-28 available on standard Pico
 * Pin 29 is VSYS sense (ADC only)
 */
#define GPIO_PIN_0      0
#define GPIO_PIN_1      1
#define GPIO_PIN_2      2
#define GPIO_PIN_3      3
#define GPIO_PIN_4      4
#define GPIO_PIN_5      5
#define GPIO_PIN_6      6
#define GPIO_PIN_7      7
#define GPIO_PIN_8      8
#define GPIO_PIN_9      9
#define GPIO_PIN_10     10
#define GPIO_PIN_11     11
#define GPIO_PIN_12     12
#define GPIO_PIN_13     13
#define GPIO_PIN_14     14
#define GPIO_PIN_15     15
#define GPIO_PIN_16     16
#define GPIO_PIN_17     17
#define GPIO_PIN_18     18
#define GPIO_PIN_19     19
#define GPIO_PIN_20     20
#define GPIO_PIN_21     21
#define GPIO_PIN_22     22
#define GPIO_PIN_26     26  /* ADC capable */
#define GPIO_PIN_27     27  /* ADC capable */
#define GPIO_PIN_28     28  /* ADC capable */
#define GPIO_PIN_25     25  /* On-board LED */

/* Common GPIO configurations */
#define LED_PIN         GPIO_PIN_25

/**
 * Function prototypes
 */

/**
 * Initialize GPIO pin as digital output
 * Sets the pin to 0V (LOW) by default
 * @param pin: GPIO pin number (0-29)
 */
void gpio_init(uint8_t pin);

/**
 * Set GPIO pin to HIGH (3.3V output)
 * @param pin: GPIO pin number (0-29)
 */
void gpio_set(uint8_t pin);

/**
 * Clear GPIO pin to LOW (0V output)
 * @param pin: GPIO pin number (0-29)
 */
void gpio_clr(uint8_t pin);

/**
 * Toggle GPIO pin state
 * Switches between HIGH and LOW
 * @param pin: GPIO pin number (0-29)
 */
void gpio_toggle(uint8_t pin);

/**
 * Read current state of GPIO pin
 * @param pin: GPIO pin number (0-29)
 * @return: 1 if pin is HIGH, 0 if LOW
 */
uint8_t gpio_read(uint8_t pin);

/**
 * Initialize GPIO examples
 * Call this function to set up GPIO functionality
 */
void gpio_example_init(void);

#endif /* GPIO_EXAMPLE_H */
