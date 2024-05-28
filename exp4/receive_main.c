#include "receive_uart.h"

int main() {
    char *portname = "/dev/ttyS3";
    int fd;

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }
    set_interface_attribs(fd, B9600);

    receive_data(fd);

    close(fd);
    return 0;
}
