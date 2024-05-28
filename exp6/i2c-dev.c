#include "i2c-dev.h"
#include <errno.h>
#include <string.h>

int i2c_init(const char *i2c_dev_node_path, int slave_address)
{
    int i2c_dev_node = open(i2c_dev_node_path, O_RDWR);
    if (i2c_dev_node < 0) {
        perror("Unable to open device node");
        exit(1);
    }

    if (ioctl(i2c_dev_node, I2C_SLAVE, slave_address) < 0) {
        perror("Could not set I2C_SLAVE");
        exit(2);
    }

    return i2c_dev_node;
}

void i2c_write(int i2c_dev_node, __u8 *buffer, __u8 length)
{
    if (write(i2c_dev_node, buffer, length) != length) {
        perror("Could not write data");
        exit(3);
    }
}

