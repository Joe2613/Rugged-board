#ifndef I2C_DEV_H
#define I2C_DEV_H

#include <linux/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h> // Include this header for I2C_SLAVE

int i2c_init(const char *i2c_dev_node_path, int slave_address);
void i2c_write(int i2c_dev_node, __u8 *buffer, __u8 length);

#endif /* I2C_DEV_H */

