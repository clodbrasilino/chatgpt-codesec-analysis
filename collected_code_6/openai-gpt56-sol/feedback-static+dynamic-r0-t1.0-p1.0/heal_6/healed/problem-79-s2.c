#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool has_odd_length(size_t length)
{
    return (length & 1U) != 0U;
}

int main(void)
{
    size_t length = 0U;
    int character;

    while ((character = getchar()) != EOF && character != '\n') {
        if (length == SIZE_MAX) {
            return 1;
        }
        ++length;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        return 1;
    }

    if (puts(has_odd_length(length) ? "Odd" : "Even") == EOF) {
        return 1;
    }

    return 0;
}