#include <ctype.h>
#include <stddef.h>
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