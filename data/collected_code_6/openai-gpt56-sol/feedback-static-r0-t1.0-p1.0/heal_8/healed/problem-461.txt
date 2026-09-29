#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_uppercase(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isupper((unsigned char)*str) != 0) {
            ++count;
        }
        ++str;
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    for (;;) {
        ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 2 > capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 128 : capacity;
            char *temporary;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (printf("%zu\n", count_uppercase(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}