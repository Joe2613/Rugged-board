#ifndef LIQUIDCRYSTAL_PCF8574_H
#define LIQUIDCRYSTAL_PCF8574_H

#include "stdint.h"
#include "i2c-dev.h"

void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void setCursor(int a, int b);
void lcd_clear(void);

#endif /* LIQUIDCRYSTAL_PCF8574_H */

