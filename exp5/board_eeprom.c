#include "board_eeprom.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// EEPROM path
static const char EEPROM_FILE_BOARD[] = "/sys/class/i2c-adapter/i2c-0/0-0050/eeprom";

// Read board EEPROM
int ReadBoardEEPROM(cBoardEEPROM* boardEEPROM) {
    int fd = 0;
    int readBytes = 0;
    memset(boardEEPROM, 0, sizeof(cBoardEEPROM));

    if ((fd = open(EEPROM_FILE_BOARD, O_RDONLY)) < 0) {
        printf("EEPROM_FILE_BOARD open error: %s\n", strerror(errno));
        return -1;
    }

    readBytes = read(fd, (void*)boardEEPROM, sizeof(cBoardEEPROM));
    if (readBytes < 0) {
        printf("EEPROM_FILE_BOARD read error: %s\n", strerror(errno));
        close(fd);
        return -1;
    }
    close(fd);

    return 0;
}

// Write board EEPROM 
void WriteBoardEEPROM(cBoardEEPROM* boardEEPROM) {
    int fd = 0;
    int writeBytes = 0;

    if ((fd = open(EEPROM_FILE_BOARD, O_WRONLY)) < 0) {
        printf("EEPROM_FILE_BOARD open error: %s\n", strerror(errno));
        return;
    }

    writeBytes = write(fd, (void*)boardEEPROM, sizeof(cBoardEEPROM));
    if (writeBytes < sizeof(cBoardEEPROM)) {
        if (writeBytes < 0)
            printf("EEPROM_FILE_BOARD write error : %s\n", strerror(errno));
        else
            printf("EEPROM_FILE_BOARD write error : Partial write to EEPROM (%d)\n", writeBytes);
    }
    close(fd);
}

