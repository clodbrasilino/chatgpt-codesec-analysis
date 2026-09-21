#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_numeric_values(const unsigned char *data, size_t length, int *in_number)
{
    size_t count = 0;

    if (data == NULL || in_number == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (isdigit((unsigned char)data[i])) {
            if (!*in_number) {
                ++count;
                *in_number = 1;
            }
        } else {
            *in_number = 0;
        }
    }

    return count;
}

int main(void)
{
    unsigned char *buffer = NULL;
    const size_t buffer_size = 4096;
    size_t count = 0;
    size_t length;
    int in_number = 0;
    int status = EXIT_SUCCESS;

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    while ((length = fread(buffer, 1, buffer_size, stdin)) != 0) {
        count += count_numeric_values(buffer, length, &in_number);
    }

    if (ferror(stdin) || printf("%zu\n", count) < 0) {
        status = EXIT_FAILURE;
    }

    free(buffer);
    return status;
}