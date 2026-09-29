#include <stdio.h>
#include <stdlib.h>

static int count_lists_in_tuple(const char *tuple, size_t *count)
{
    size_t lists = 0;
    size_t square_depth = 0;
    char quote = '\0';
    int escaped = 0;

    if (tuple == NULL || count == NULL) {
        return -1;
    }

    for (size_t i = 0; tuple[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)tuple[i];

        if (quote != '\0') {
            if (escaped) {
                escaped = 0;
            } else if (ch == '\\') {
                escaped = 1;
            } else if (ch == (unsigned char)quote) {
                quote = '\0';
            }
            continue;
        }

        if (ch == '\'' || ch == '"') {
            quote = (char)ch;
        } else if (ch == '[') {
            if (square_depth == 0) {
                ++lists;
            }
            ++square_depth;
        } else if (ch == ']') {
            if (square_depth == 0) {
                return -1;
            }
            --square_depth;
        }
    }

    if (quote != '\0' || square_depth != 0) {
        return -1;
    }

    *count = lists;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t count = 0;
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)c;
    }

    if (ferror(stdin) || (c == EOF && length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }
        input = new_input;
    }

    input[length] = '\0';

    if (count_lists_in_tuple(input, &count) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}