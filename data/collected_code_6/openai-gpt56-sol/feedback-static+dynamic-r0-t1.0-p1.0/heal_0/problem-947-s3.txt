#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t shortest_word_length(const char *text)
{
    size_t shortest = SIZE_MAX;
    size_t current = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isspace((unsigned char)*text)) {
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

    return shortest == SIZE_MAX ? 0 : shortest;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (shortest_word_length(input) == 0) {
        printf("No words found.\n");
    } else {
        printf("%zu\n", shortest_word_length(input));
    }

    return EXIT_SUCCESS;
}