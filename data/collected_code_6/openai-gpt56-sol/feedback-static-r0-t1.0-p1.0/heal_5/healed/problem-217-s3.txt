#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};
    size_t i;

    if (result == NULL || (data == NULL && length != 0U)) {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        unsigned int index = data[i];

        if (seen[index] != 0U) {
            *result = data[i];
            return 1;
        }

        seen[index] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    unsigned char repeated = 0U;
    int status;

    for (;;) {
        int ch = getchar();

        if (ch == EOF) {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_input;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    fputs("Input is too large.\n", stderr);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2U;
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

        input[length] = (unsigned char)ch;
        ++length;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    status = find_first_repeated_character(input, length, &repeated);
    free(input);

    if (status < 0) {
        fputs("Invalid argument.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 1) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    } else {
        if (puts("No repeated character found.") == EOF) {
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}