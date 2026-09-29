#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uintmax_t count = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        if (islower((unsigned char)character) != 0) {
            if (count == UINTMAX_MAX) {
                return 1;
            }
            ++count;
        }
    }

    if (ferror(stdin) != 0) {
        return 1;
    }

    if (printf("%ju\n", count) < 0) {
        return 1;
    }

    return 0;
}