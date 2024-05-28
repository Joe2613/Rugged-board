#ifndef RECEIVE_UART_H
#define RECEIVE_UART_H

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

// Function prototypes
int set_interface_attribs(int fd, int speed);
void receive_data(int fd);

#endif /* RECEIVE_UART_H */

