#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_present(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = UINT32_MAX;

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;
        uint64_t square = middle * middle;

        if (square == number) {
            return true;
        }

        if (middle > number / middle) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return false;
}

int main(void)
{
    uintmax_t value;
    int result;

    errno = 0;
    result = scanf("%" SCNuMAX, &value);

    if (result != 1 || errno == ERANGE || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    int ch;
    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch != EOF) {
        return EXIT_FAILURE;
    }

    puts(is_present((uint64_t)value) ? "Present" : "Not present");
    return EXIT_SUCCESS;
}