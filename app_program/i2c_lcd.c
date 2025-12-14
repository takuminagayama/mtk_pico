/*
 * I2C LCD Control Implementation for AQM0802
 * Raspberry Pi Pico I2C Interface
 */

#include <stdint.h>
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include "i2c_lcd.h"

/* RP2040 I2C Register Definitions */
#define I2C0_BASE           0x40044000
#define I2C1_BASE           0x40048000

/* I2C Registers */
#define I2C_CON             0x00
#define I2C_TAR             0x04
#define I2C_DATA_CMD        0x10
#define I2C_STATUS          0x70
#define I2C_RXFLR           0x78
#define I2C_TXFLR           0x7C
#define I2C_CLR_INTR        0x40
#define I2C_FS_SCL_HCNT     0x0C
#define I2C_FS_SCL_LCNT     0x10
#define I2C_SDA_HOLD        0x7C

/* I2C Status Flags */
#define I2C_STATUS_ACTIVITY 0x01
#define I2C_STATUS_TFNF     0x02
#define I2C_STATUS_TFE      0x04
#define I2C_STATUS_RFNE     0x08
#define I2C_STATUS_RFF      0x10

/* Register access macros */
#define REG_RD(addr)        (*(volatile uint32_t *)(addr))
#define REG_WR(addr, val)   (*(volatile uint32_t *)(addr)) = (val)

/* Using I2C1 (GP26=SDA, GP27=SCL) */
#define I2C_BASE            I2C1_BASE

/* RP2040 base addresses (already defined in sysdef.h) */
#define GPIO_PAD(n)         (PADS_BANK0_BASE + 4 + (n) * 4)

/**
 * Initialize I2C1 with GPIO26 (SDA) and GPIO27 (SCL)
 */
int i2c_lcd_init(void)
{
	tm_printf((UB*)"[I2C-LCD] Initializing I2C1 and LCD\n");
	
	/* Configure GPIO26 and GPIO27 as I2C1 */
	/* GPIO26: I2C1 SDA (function 3) */
	/* GPIO27: I2C1 SCL (function 3) */
	
	/* Set GPIO function to I2C */
	REG_WR(GPIO_CTRL(26), 3);  /* GPIO26 → I2C1 SDA */
	REG_WR(GPIO_CTRL(27), 3);  /* GPIO27 → I2C1 SCL */
	
	/* Enable pull-ups on SDA/SCL */
	REG_RD(GPIO_PAD(26));  /* Enable pull-up for SDA */
	REG_RD(GPIO_PAD(27));  /* Enable pull-up for SCL */
	
	/* Reset I2C */
	REG_WR(RESETS_RESET, REG_RD(RESETS_RESET) | (1 << 14));  /* I2C1 reset */
	while ((REG_RD(RESETS_RESET_DONE) & (1 << 14)) == 0);    /* Wait reset done */
	
	/* Configure I2C */
	REG_WR(I2C_BASE + I2C_CON, 0x65);        /* Enable I2C, fast mode */
	REG_WR(I2C_BASE + I2C_TAR, AQM0802_ADDR); /* Target address */
	
	/* Set clock: 125MHz / (16 + 55 + 16 + 55) = ~100kHz */
	REG_WR(I2C_BASE + I2C_FS_SCL_HCNT, 55);
	REG_WR(I2C_BASE + I2C_FS_SCL_LCNT, 55);
	
	tk_dly_tsk(100);  /* Wait for I2C to settle */
	
	/* LCD Initialization Sequence */
	/* 1. Set 4-bit mode (via I2C) */
	i2c_lcd_cmd(0x38);  /* Function set: 8-bit, 2-line, 5x8 */
	tk_dly_tsk(5);
	
	i2c_lcd_cmd(0x39);  /* Function set: IS=1 for extended instruction */
	tk_dly_tsk(5);
	
	i2c_lcd_cmd(0x14);  /* Internal OSC frequency */
	tk_dly_tsk(5);
	
	i2c_lcd_cmd(0x70);  /* Contrast set */
	tk_dly_tsk(5);
	
	i2c_lcd_cmd(0x56);  /* Power/ICON/Contrast control */
	tk_dly_tsk(5);
	
	i2c_lcd_cmd(0x6C);  /* Follower control */
	tk_dly_tsk(200);
	
	i2c_lcd_cmd(0x38);  /* Function set: IS=0 */
	tk_dly_tsk(5);
	
	i2c_lcd_cmd(0x0C);  /* Display ON, cursor OFF */
	tk_dly_tsk(5);
	
	i2c_lcd_cmd(0x01);  /* Clear display */
	tk_dly_tsk(200);
	
	i2c_lcd_cmd(0x06);  /* Entry mode: auto-increment */
	tk_dly_tsk(5);
	
	tm_printf((UB*)"[I2C-LCD] Initialization complete\n");
	return 0;
}

/**
 * Wait for I2C FIFO to be ready
 */
static void i2c_wait_fifo(void)
{
	int timeout = 10000;
	while ((REG_RD(I2C_BASE + I2C_STATUS) & I2C_STATUS_TFNF) == 0 && timeout-- > 0) {
		tk_dly_tsk(1);
	}
}

/**
 * Send I2C byte
 */
static int i2c_write_byte(uint8_t byte)
{
	i2c_wait_fifo();
	REG_WR(I2C_BASE + I2C_DATA_CMD, byte);
	
	/* Wait for transmission */
	int timeout = 10000;
	while ((REG_RD(I2C_BASE + I2C_STATUS) & I2C_STATUS_ACTIVITY) && timeout-- > 0) {
		tk_dly_tsk(1);
	}
	
	return (timeout > 0) ? 0 : -1;
}

/**
 * Send command to LCD
 */
int i2c_lcd_cmd(uint8_t cmd)
{
	uint8_t data[2];
	data[0] = 0x00;  /* Control byte: command mode */
	data[1] = cmd;
	
	return i2c_write_byte(data[0]) | i2c_write_byte(data[1]);
}

/**
 * Send data (character) to LCD
 */
int i2c_lcd_data(uint8_t data)
{
	uint8_t byte[2];
	byte[0] = 0x40;  /* Control byte: data mode */
	byte[1] = data;
	
	return i2c_write_byte(byte[0]) | i2c_write_byte(byte[1]);
}

/**
 * Write string to LCD
 */
int i2c_lcd_write(const char *str)
{
	int count = 0;
	
	if (str == NULL) return -1;
	
	while (*str && count < 8) {  /* AQM0802 is 8 characters wide */
		if (i2c_lcd_data((uint8_t)*str) == 0) {
			count++;
			str++;
		} else {
			return -1;  /* I2C error */
		}
		tk_dly_tsk(1);
	}
	
	return count;
}

/**
 * Clear LCD display
 */
int i2c_lcd_clear(void)
{
	return i2c_lcd_cmd(0x01);
}

/**
 * Set cursor position
 */
int i2c_lcd_set_cursor(uint8_t line, uint8_t col)
{
	if (line > 1 || col > 7) return -1;
	
	uint8_t addr = 0x80 + (line * 0x40) + col;
	return i2c_lcd_cmd(addr);
}

/**
 * Display on/off
 */
int i2c_lcd_display_on_off(int on)
{
	uint8_t cmd = on ? 0x0C : 0x08;
	return i2c_lcd_cmd(cmd);
}
