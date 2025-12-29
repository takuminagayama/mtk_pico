/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP
 *
 *    Copyright (C) 2022-2023 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2023/05.
 *
 *----------------------------------------------------------------------
 */

/*
 *	app_main.c
 *	Application main program for RaspberryPi Pico
 *	LCD Display: AQM0802 via I2C1 (GP26/GP27)
 */

#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include <bsp/libbsp.h>
#include "i2c_lcd.h"
#include "gpio_control.h"

LOCAL void task_1(INT stacd, void *exinf);
LOCAL void task_2(INT stacd, void *exinf);
//LOCAL void lcd_demo_task(INT stacd, void *exinf);
LOCAL ID	tskid_1;
LOCAL ID	tskid_2;
//LOCAL ID	tskid_lcd;

LOCAL T_CTSK	ctsk_1 = {
	.itskpri	= 10,
	.stksz		= 1024,
	.task		= task_1,
	.tskatr		= TA_HLNG | TA_RNG3,
};

LOCAL T_CTSK	ctsk_2 = {
	.itskpri	= 10,
	.stksz		= 1024,
	.task		= task_2,
	.tskatr		= TA_HLNG | TA_RNG3,
};
#if 0
LOCAL T_CTSK	ctsk_lcd = {
	.itskpri	= 11,
	.stksz		= 2048,
	.task		= lcd_demo_task,
	.tskatr		= TA_HLNG | TA_RNG3,
};
#endif
LOCAL void task_1(INT stacd, void *exinf)
{
	/* P25 : On board LED - Blink */
	int count = 0;
	while(1) {
		gpio_set_val(25, 1);
		tm_printf((UB*)"[LED-Task] ON (count=%d)\n", count);
		tk_dly_tsk(1000);

		gpio_set_val(25, 0);
		tm_printf((UB*)"[LED-Task] OFF (count=%d)\n", count);
		tk_dly_tsk(1000);
		count++;
	}
}

LOCAL void task_2(INT stacd, void *exinf)
{
	/* P25 : On board LED - Blink */
	int count = 0;
	while(1) {
		gpio_set_val( 2, 1);
		gpio_set_val( 3, 1);
		gpio_set_val( 4, 1);
		gpio_set_val( 5, 1);
		gpio_set_val( 6, 1);
		gpio_set_val( 7, 1);
		gpio_set_val( 8, 1);
		gpio_set_val( 9, 1);
		gpio_set_val(10, 1);
		gpio_set_val(11, 1);
		gpio_set_val(12, 1);
		gpio_set_val(13, 1);
		gpio_set_val(14, 1);
		gpio_set_val(15, 1);
		tm_printf((UB*)"[LED2-Task] ON (count=%d)\n", count);
		tk_dly_tsk(1000);

		gpio_set_val( 2, 0);
		gpio_set_val( 3, 0);
		gpio_set_val( 4, 0);
		gpio_set_val( 5, 0);
		gpio_set_val( 6, 0);
		gpio_set_val( 7, 0);
		gpio_set_val( 8, 0);
		gpio_set_val( 9, 0);
		gpio_set_val(10, 0);
		gpio_set_val(11, 0);
		gpio_set_val(12, 0);
		gpio_set_val(13, 0);
		gpio_set_val(14, 0);
		gpio_set_val(15, 0);
		tm_printf((UB*)"[LED2-Task] OFF (count=%d)\n", count);
		tk_dly_tsk(1000);
		count++;
	}
}

#if 0
LOCAL void lcd_demo_task(INT stacd, void *exinf)
{
	tm_printf((UB*)"[LCD-Task] Starting LCD demo\n");
	
	/* Initialize I2C and LCD */
	if (i2c_lcd_init() != 0) {
		tm_printf((UB*)"[LCD-Task] Error: LCD initialization failed\n");
		return;
	}
	
	tm_printf((UB*)"[LCD-Task] LCD initialized successfully\n");
	
	/* Display "Hello" on first line */
	i2c_lcd_set_cursor(0, 0);  /* Line 0, Column 0 */
	i2c_lcd_write("Hello");
	tm_printf((UB*)"[LCD-Task] Displayed 'Hello' on line 1\n");
	
	tk_dly_tsk(2000);
	
	/* Display "Pico" on second line */
	i2c_lcd_set_cursor(1, 0);  /* Line 1, Column 0 */
	i2c_lcd_write("Pico");
	tm_printf((UB*)"[LCD-Task] Displayed 'Pico' on line 2\n");
	
	/* Cycle display animation */
	int counter = 0;
	while(1) {
		tk_dly_tsk(3000);
		
		/* Clear display */
		i2c_lcd_clear();
		tm_printf((UB*)"[LCD-Task] Cleared display (counter=%d)\n", counter);
		
		tk_dly_tsk(500);
		
		/* Show counter messages in rotation */
		i2c_lcd_set_cursor(0, 0);
		if (counter % 3 == 0) {
			i2c_lcd_write("Count:0");
		} else if (counter % 3 == 1) {
			i2c_lcd_write("Count:1");
		} else {
			i2c_lcd_write("Count:2");
		}
		
		i2c_lcd_set_cursor(1, 0);
		i2c_lcd_write("Ready");
		
		tm_printf((UB*)"[LCD-Task] Displayed counter\n");
		counter++;
	}
}
#endif 

EXPORT INT usermain(void)
{
	tm_printf((UB*)"\n");
	tm_printf((UB*)"===================================\n");
	tm_printf((UB*)"User program started\n");
	tm_printf((UB*)"LCD: AQM0802 on I2C1\n");
	tm_printf((UB*)"===================================\n");

	/* Initialize all GPIO pins */
	gpio_init_all();

	/* Create LED blink task */
	tskid_1 = tk_cre_tsk(&ctsk_1);
	tm_printf((UB*)"Task-1 (LED) created: ID=%d\n", tskid_1);
	tk_sta_tsk(tskid_1, 0);

	/* Create LED blink task */
	tskid_2 = tk_cre_tsk(&ctsk_2);
	tm_printf((UB*)"Task-1 (LED) created: ID=%d\n", tskid_2);
	tk_sta_tsk(tskid_2, 0);
#if 0
	/* Create LCD demo task */
	tskid_lcd = tk_cre_tsk(&ctsk_lcd);
	tm_printf((UB*)"Task-LCD created: ID=%d\n", tskid_lcd);
	tk_sta_tsk(tskid_lcd, 0);
#endif 
	tm_printf((UB*)"All tasks started\n");
	tk_slp_tsk(TMO_FEVR);
	return 0;
}