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
    unsigned char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof buffer, stdin)) != 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            process_character(buffer[i], &current, &shortest);
        }
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