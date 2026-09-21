#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

size_t shortest_word_length(const char *text)
{
    size_t shortest = 0;
    size_t current = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isspace((unsigned char)*text)) {
            if (current != 0 && (shortest == 0 || current < shortest)) {
                shortest = current;
            }
            current = 0;
        } else {
            ++current;
        }
        ++text;
    }

    if (current != 0 && (shortest == 0 || current < shortest)) {
        shortest = current;
    }

    return shortest;
}

int main(void)
{
    size_t shortest = 0;
    size_t current = 0;
    int ch;

    while ((ch = getchar()) != EOF) {
        if (isspace((unsigned char)ch)) {
            if (current != 0 && (shortest == 0 || current < shortest)) {
                shortest = current;
            }
            current = 0;
        } else {
            ++current;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (current != 0 && (shortest == 0 || current < shortest)) {
        shortest = current;
    }

    printf("%zu\n", shortest);
    return 0;
}