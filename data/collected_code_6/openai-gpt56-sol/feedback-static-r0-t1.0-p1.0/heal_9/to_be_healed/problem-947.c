#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

static void process_character(unsigned char ch, size_t *current, size_t *shortest)
{
    if (isspace((int)ch)) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];

    while (!feof(stdin)) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            process_character(buffer[i], &current, &shortest);
        }

        if (ferror(stdin)) {
            return 1;
        }
    }

    if (current != 0 && (shortest == 0 || current < shortest)) {
        shortest = current;
    }

    if (printf("%zu\n", shortest) < 0) {
        return 1;
    }

    return 0;
}