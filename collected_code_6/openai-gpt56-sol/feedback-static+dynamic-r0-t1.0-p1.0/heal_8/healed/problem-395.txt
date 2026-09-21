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
    unsigned char result;
    int status = EXIT_SUCCESS;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            unsigned char *temporary;

            if (capacity == 0) {
                new_capacity = 1024;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    status = EXIT_FAILURE;
                    break;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                status = EXIT_FAILURE;
                break;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                status = EXIT_FAILURE;
                break;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (status == EXIT_SUCCESS && character == EOF && ferror(stdin)) {
        status = EXIT_FAILURE;
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