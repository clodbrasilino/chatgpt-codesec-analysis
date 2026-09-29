#include <stdbool.h>
#include <stdio.h>

static bool has_odd_length(size_t length)
{
    return length % 2U != 0U;
}

int main(void)
{
    size_t length = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        ++length;
    }

    if (character == EOF) {
        if (ferror(stdin) || length == 0U) {
            return 1;
        }
    }

    puts(has_odd_length(length) ? "Odd" : "Even");
    return 0;
}