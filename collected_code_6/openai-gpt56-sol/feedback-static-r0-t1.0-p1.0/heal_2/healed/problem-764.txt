#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_numeric_values(const char *text)
{
    size_t count = 0;
    int in_number = 0;

    if (text == NULL) {
        return 0;
    }

    for (const unsigned char *p = (const unsigned char *)text; *p != '\0'; ++p) {
        if (isdigit((int)*p)) {
            if (!in_number) {
                ++count;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
    }

    return count;
}

int main(void)
{
    size_t count = 0;
    int in_number = 0;
    unsigned char *buffer = malloc(4096);

    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, 1, 4096, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (isdigit((int)buffer[i])) {
                if (!in_number) {
                    ++count;
                    in_number = 1;
                }
            } else {
                in_number = 0;
            }
        }

        if (bytes_read < 4096) {
            if (ferror(stdin)) {
                free(buffer);
                return EXIT_FAILURE;
            }
            break;
        }
    }

    free(buffer);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}