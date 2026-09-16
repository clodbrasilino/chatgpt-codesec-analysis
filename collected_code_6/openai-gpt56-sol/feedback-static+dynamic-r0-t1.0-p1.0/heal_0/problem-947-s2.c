#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static size_t shortest_word_length(const char *text)
{
    size_t shortest = 0;
    size_t current = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isalnum((unsigned char)*text) != 0) {
            ++current;
        } else if (current != 0) {
            if (shortest == 0 || current < shortest) {
                shortest = current;
            }
            current = 0;
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
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        if (ferror(stdin) != 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    printf("%zu\n", shortest_word_length(line));
    free(line);

    return EXIT_SUCCESS;
}