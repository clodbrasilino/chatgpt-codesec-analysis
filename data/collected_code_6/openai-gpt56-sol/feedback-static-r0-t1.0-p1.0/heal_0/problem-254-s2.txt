#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_words_starting_with_a_or_e(const char *text)
{
    const unsigned char *cursor = (const unsigned char *)text;

    while (*cursor != '\0') {
        const unsigned char *start;
        size_t length;

        while (*cursor != '\0' && !isalpha(*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            break;
        }

        start = cursor;

        while (*cursor != '\0' && isalpha(*cursor)) {
            ++cursor;
        }

        length = (size_t)(cursor - start);

        if (tolower(*start) == 'a' || tolower(*start) == 'e') {
            if (printf("%.*s\n", (int)length, (const char *)start) < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (find_words_starting_with_a_or_e(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}