#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_length(size_t length)
{
    return (length & 1U) != 0U;
}

int main(void)
{
    size_t length = 0U;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length == SIZE_MAX) {
            return EXIT_FAILURE;
        }

        ++length;
    }

    if (character == EOF && (ferror(stdin) || length == 0U)) {
        return EXIT_FAILURE;
    }

    if (puts(has_odd_length(length) ? "Odd" : "Even") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}