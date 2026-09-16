#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

size_t shortest_word_length(const char *text)
{
    size_t shortest = (size_t)-1;
    size_t current = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isspace((unsigned char)*text) != 0) {
            if (current > 0 && current < shortest) {
                shortest = current;
            }
            current = 0;
        } else {
            ++current;
        }
        ++text;
    }

    if (current > 0 && current < shortest) {
        shortest = current;
    }

    return shortest == (size_t)-1 ? 0 : shortest;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    printf("%zu\n", shortest_word_length(input));
    return 0;
}