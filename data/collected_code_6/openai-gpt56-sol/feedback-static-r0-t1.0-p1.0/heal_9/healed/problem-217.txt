#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const char *str, unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1] = {0};

    if (str == NULL || result == NULL) {
        return 0;
    }

    while (*str != '\0') {
        unsigned char ch = (unsigned char)*str++;

        if (seen[ch] != 0) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char repeated;
    int status = EXIT_SUCCESS;

    for (;;) {
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin)) {
                status = EXIT_FAILURE;
            }
            break;
        }

        if (length > SIZE_MAX - 2) {
            status = EXIT_FAILURE;
            break;
        }

        size_t required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                status = EXIT_FAILURE;
                break;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (status == EXIT_SUCCESS && length != 0) {
        input[length] = '\0';

        if (find_first_repeated_character(input, &repeated)) {
            if (putchar(repeated) == EOF || putchar('\n') == EOF) {
                status = EXIT_FAILURE;
            }
        } else if (puts("No repeated character") == EOF) {
            status = EXIT_FAILURE;
        }
    }

    free(input);
    return status;
}