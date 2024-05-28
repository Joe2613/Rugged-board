#include "LiquidCrystal_PCF8574.h"
#include <unistd.h>

int main(void)
{
    lcd_init();
    setCursor(0, 0);
    lcd_send_string("Prog for I2C on");
    setCursor(0, 1);
    lcd_send_string("STM32F411RE");
    usleep(2000000);
    lcd_clear();

    while (1) {
        setCursor(0, 0);
        lcd_send_string("DEVA");
        setCursor(0, 1);
        lcd_send_string("SHIVA");
        usleep(1000000);
    }

    return 0;
}

