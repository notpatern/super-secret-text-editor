#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

struct termios originalterm;



void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalterm);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &originalterm);
    atexit(disableRawMode);
    struct termios raw = originalterm;
    raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON | ICRNL);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag &= ~(CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
  enableRawMode();
    char character;
    while (read(STDIN_FILENO, &character, 1) == 1 && character != 'q') {
        if (iscntrl(character)) {
            printf("%d\r\n", character);
        }
        else {
            printf("%d ('%c')\r\n", character, character);
        }
    }
    return 0;
}
