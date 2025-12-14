/*
 * I2C LCD Control Header for AQM0802 (8x2 Character LCD)
 * Connection: 
 *   GP26 (SDA) - Pin 31
 *   GP27 (SCL) - Pin 32
 */

#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <stdint.h>
#include <tk/tkernel.h>

/* AQM0802 I2C Address */
#define AQM0802_ADDR    0x3E  /* 7-bit address */

/* LCD Commands */
#define LCD_CMD_CLEAR           0x01
#define LCD_CMD_HOME            0x02
#define LCD_CMD_ENTRY_MODE      0x04
#define LCD_CMD_DISPLAY_CTRL    0x08
#define LCD_CMD_SHIFT           0x10
#define LCD_CMD_FUNCTION_SET    0x20
#define LCD_CMD_CGRAM_ADDR      0x40
#define LCD_CMD_DDRAM_ADDR      0x80

/* Entry Mode Flags */
#define LCD_ENTRY_INCR          0x02
#define LCD_ENTRY_NOSHIFT       0x00

/* Display Control Flags */
#define LCD_DISPLAY_ON          0x04
#define LCD_CURSOR_ON           0x02
#define LCD_BLINK_ON            0x01

/* Function Set Flags */
#define LCD_4BIT_MODE           0x00
#define LCD_8BIT_MODE           0x10
#define LCD_1LINE               0x00
#define LCD_2LINE               0x08
#define LCD_5X8_DOTS            0x00
#define LCD_5X10_DOTS           0x04

/**
 * Initialize I2C and LCD
 * @return: 0 on success, -1 on error
 */
int i2c_lcd_init(void);

/**
 * Send command to LCD
 * @cmd: Command byte
 * @return: 0 on success, -1 on error
 */
int i2c_lcd_cmd(uint8_t cmd);

/**
 * Send data (character) to LCD
 * @data: Data byte
 * @return: 0 on success, -1 on error
 */
int i2c_lcd_data(uint8_t data);

/**
 * Write string to LCD
 * @str: String to write
 * @return: Number of characters written
 */
int i2c_lcd_write(const char *str);

/**
 * Clear LCD display
 * @return: 0 on success, -1 on error
 */
int i2c_lcd_clear(void);

/**
 * Set cursor position
 * @line: Line number (0 or 1)
 * @col: Column number (0-7)
 * @return: 0 on success, -1 on error
 */
int i2c_lcd_set_cursor(uint8_t line, uint8_t col);

/**
 * Display on/off
 * @on: 1 for on, 0 for off
 * @return: 0 on success, -1 on error
 */
int i2c_lcd_display_on_off(int on);

#endif /* I2C_LCD_H */
