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
        return 0;
    }

    for (i = 0U; i < length; ++i) {
        unsigned int index = (unsigned int)data[i];

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
    unsigned char repeated;
    int ch;
    int status = EXIT_SUCCESS;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_input;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    status = EXIT_FAILURE;
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity * sizeof(*input));
            if (new_input == NULL) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length] = (unsigned char)ch;
        ++length;
    }

    if (ferror(stdin)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (find_first_repeated_character(input, length, &repeated) != 0) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            status = EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        status = EXIT_FAILURE;
    }

cleanup:
    free(input);
    return status;
}