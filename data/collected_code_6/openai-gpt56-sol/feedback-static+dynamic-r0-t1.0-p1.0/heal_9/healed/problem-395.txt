#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_first_non_repeated(const unsigned char *data,
                                   size_t length,
                                   unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t i;

    if (result == NULL || (data == NULL && length != 0)) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        if (frequencies[data[i]] < 2) {
            ++frequencies[data[i]];
        }
    }

    for (i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1) {
            *result = data[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char result = 0;
    int status = EXIT_SUCCESS;

    for (;;) {
        unsigned char buffer[4096];
        size_t bytes_read;
        size_t i;
        int line_complete = 0;

        bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        for (i = 0; i < bytes_read; ++i) {
            size_t required;

            if (buffer[i] == '\n') {
                line_complete = 1;
                break;
            }

            if (length == SIZE_MAX) {
                status = EXIT_FAILURE;
                break;
            }

            required = length + 1;

            if (required > capacity) {
                size_t new_capacity;
                unsigned char *temporary;

                new_capacity = capacity == 0 ? 1024 : capacity;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2) {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2;
                }

                temporary = realloc(input, new_capacity);
                if (temporary == NULL) {
                    status = EXIT_FAILURE;
                    break;
                }

                input = temporary;
                capacity = new_capacity;
            }

            input[length++] = buffer[i];
        }

        if (status != EXIT_SUCCESS || line_complete) {
            break;
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                status = EXIT_FAILURE;
            }
            break;
        }
    }

    if (status == EXIT_SUCCESS) {
        if (find_first_non_repeated(input, length, &result)) {
            if (putchar((int)result) == EOF || putchar('\n') == EOF) {
                status = EXIT_FAILURE;
            }
        } else if (puts("No non-repeated character found") == EOF) {
            status = EXIT_FAILURE;
        }
    }

    free(input);
    return status;
}