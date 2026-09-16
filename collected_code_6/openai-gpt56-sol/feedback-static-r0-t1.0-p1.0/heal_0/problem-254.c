#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_words_starting_with_a_or_e(const char *text)
{
    const unsigned char *current = (const unsigned char *)text;

    while (*current != '\0') {
        const unsigned char *start;
        size_t length;

        while (*current != '\0' && isspace(*current)) {
            ++current;
        }

        if (*current == '\0') {
            break;
        }

        start = current;

        while (*current != '\0' && !isspace(*current)) {
            ++current;
        }

        length = (size_t)(current - start);

        if (tolower(start[0]) == 'a' || tolower(start[0]) == 'e') {
            if (printf("%.*s\n", (int)length, (const char *)start) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    ssize_t length;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return feof(stdin) ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    if (find_words_starting_with_a_or_e(input) != EXIT_SUCCESS) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}