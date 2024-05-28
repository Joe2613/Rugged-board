#include "LiquidCrystal_PCF8574.h"
#include <unistd.h>
#include <string.h>

#define SLAVE_ADDRESS_LCD 0x27

static int i2c_dev_node;

void lcd_write_i2c(__u8 *buffer, __u8 length)
{
    i2c_write(i2c_dev_node, buffer, length);
}

void lcd_send_cmd(char cmd)
{
    char data_u = (cmd & 0xF0);
    char data_l = ((cmd << 4) & 0xF0);
    uint8_t data_t[4] = {
        data_u | 0x0C, // en=1, rs=0
        data_u | 0x08, // en=0, rs=0
        data_l | 0x0C, // en=1, rs=0
        data_l | 0x08  // en=0, rs=0
    };
    lcd_write_i2c((__u8 *)data_t, 4);
}

void lcd_send_data(char data)
{
    char data_u = (data & 0xF0);
    char data_l = ((data << 4) & 0xF0);
    uint8_t data_t[4] = {
        data_u | 0x0D, // en=1, rs=1
        data_u | 0x09, // en=0, rs=1
        data_l | 0x0D, // en=1, rs=1
        data_l | 0x09  // en=0, rs=1
    };
    lcd_write_i2c((__u8 *)data_t, 4);
}

void setCursor(int a, int b)
{
    static const uint8_t row_offsets[] = {0x80, 0xC0, 0x94, 0xD4};
    if (b < 0 || b >= sizeof(row_offsets) / sizeof(row_offsets[0])) {
        return; // Invalid row
    }
    lcd_send_cmd(row_offsets[b]);
    for (int i = 0; i < a; ++i) {
        lcd_send_cmd(0x14);
    }
}

void lcd_send_string(char *str)
{
    while (*str) {
        lcd_send_data(*str++);
    }
}

void lcd_init(void)
{
    i2c_dev_node = i2c_init("/dev/i2c-0", SLAVE_ADDRESS_LCD);
    usleep(50000);  // wait for >40ms
    lcd_send_cmd(0x30);
    usleep(5000);  // wait for >4.1ms
    lcd_send_cmd(0x30);
    usleep(160);  // wait for >100us
    lcd_send_cmd(0x30);
    usleep(160);
    lcd_send_cmd(0x20);  // 4bit mode
    usleep(160);

    // display initialization
    lcd_send_cmd(0x28); // Function set: DL=0 (4 bit mode), N=1 (2 line display), F=0 (5x8 characters)
    usleep(160);
    lcd_send_cmd(0x08); // Display off
    usleep(160);
    lcd_send_cmd(0x01);  // Clear display
    usleep(160);
    lcd_send_cmd(0x06); // Entry mode set: I/D=1 (increment cursor), S=0 (no shift)
    usleep(160);
    lcd_send_cmd(0x0C); // Display on: D=1, C=0, B=0 (cursor and blink off)
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01); // Clear display
    usleep(2000); // wait for command to complete
}

