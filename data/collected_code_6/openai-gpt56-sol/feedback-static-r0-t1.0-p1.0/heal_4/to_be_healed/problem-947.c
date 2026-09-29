#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

static void process_character(int ch, size_t *current, size_t *shortest)
{
    if (isspace((unsigned char)ch)) {
        if (*current != 0 && (*shortest == 0 || *current < *shortest)) {
            *shortest = *current;
        }
        *current = 0;
    } else if (*current < SIZE_MAX) {
        ++*current;
    }
}

int main(void)
{
    size_t shortest = 0;
    size_t current = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        process_character(ch, &current, &shortest);
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (current != 0 && (shortest == 0 || current < shortest)) {
        shortest = current;
    }

    if (printf("%zu\n", shortest) < 0) {
        return 1;
    }

    return 0;
}