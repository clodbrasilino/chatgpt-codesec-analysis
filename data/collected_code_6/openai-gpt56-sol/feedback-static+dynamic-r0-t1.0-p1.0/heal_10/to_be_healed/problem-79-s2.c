#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static bool has_odd_length(size_t length)
{
    return (length & (size_t)1) != 0;
}

int main(void)
{
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length == SIZE_MAX) {
            return 1;
        }
        ++length;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (character == EOF && length == 0) {
        return 1;
    }

    return puts(has_odd_length(length) ? "Odd" : "Even") == EOF ? 1 : 0;
}