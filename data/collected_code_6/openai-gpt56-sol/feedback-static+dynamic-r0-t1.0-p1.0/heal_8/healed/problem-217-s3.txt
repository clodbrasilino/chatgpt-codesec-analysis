#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data, size_t length,
                                  unsigned char *result)
{
    unsigned char *seen;

    if (result == NULL || (data == NULL && length != 0U)) {
        return -1;
    }

    seen = calloc((size_t)UCHAR_MAX + 1U, sizeof(*seen));
    if (seen == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        const unsigned char value = data[i];

        if (seen[value] != 0U) {
            *result = value;
            free(seen);
            return 1;
        }

        seen[value] = 1U;
    }

    free(seen);
    return 0;
}

int main(void)
{
    unsigned char *seen;
    unsigned char *buffer;
    const size_t seen_size = (size_t)UCHAR_MAX + 1U;
    const size_t buffer_size = 4096U;
    int status = EXIT_SUCCESS;

    seen = calloc(seen_size, sizeof(*seen));
    buffer = malloc(buffer_size);

    if (seen == NULL || buffer == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        free(buffer);
        free(seen);
        return EXIT_FAILURE;
    }

    for (;;) {
        const size_t bytes_read = fread(buffer, sizeof(*buffer), buffer_size,
                                        stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            const unsigned char value = buffer[i];

            if (seen[value] != 0U) {
                if (fputc((int)value, stdout) == EOF ||
                    fputc('\n', stdout) == EOF) {
                    status = EXIT_FAILURE;
                }

                free(buffer);
                free(seen);
                return status;
            }

            seen[value] = 1U;
        }

        if (bytes_read < buffer_size) {
            if (ferror(stdin) != 0) {
                if (fputs("Failed to read input.\n", stderr) == EOF) {
                    status = EXIT_FAILURE;
                } else {
                    status = EXIT_FAILURE;
                }
            }

            break;
        }
    }

    if (status == EXIT_SUCCESS &&
        fputs("No repeated character found.\n", stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free(buffer);
    free(seen);
    return status;
}