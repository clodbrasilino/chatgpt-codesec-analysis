#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const char *str, unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (str == NULL || result == NULL) {
        return -1;
    }

    while (*str != '\0') {
        unsigned char ch = (unsigned char)*str++;

        if (seen[ch] != 0U) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1U;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    unsigned char repeated = 0U;
    int status;
    int ch = EOF;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity = capacity == 0U ? 128U : capacity;
            char *new_input;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0U) {
        free(input);
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    status = find_first_repeated_character(input, &repeated);
    free(input);

    if (status < 0) {
        fputs("Invalid argument.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 1) {
        printf("%c\n", (int)repeated);
    } else {
        puts("No repeated character found.");
    }

    return EXIT_SUCCESS;
}