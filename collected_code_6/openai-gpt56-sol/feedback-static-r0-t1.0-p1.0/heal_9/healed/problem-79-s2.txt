#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_length(size_t length)
{
    return (length & (size_t)1) != 0;
}

int main(void)
{
    size_t length = 0;
    char buffer[4096];

    for (;;) {
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                return EXIT_FAILURE;
            }
            break;
        }

        size_t index = 0;

        while (buffer[index] != '\0' && buffer[index] != '\n') {
            if (length == SIZE_MAX) {
                return EXIT_FAILURE;
            }

            ++length;
            ++index;
        }

        if (buffer[index] == '\n') {
            break;
        }
    }

    if (puts(has_odd_length(length) ? "Odd" : "Even") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}