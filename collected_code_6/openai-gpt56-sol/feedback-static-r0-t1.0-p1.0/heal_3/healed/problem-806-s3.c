#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t max_uppercase_run(const char *str)
{
    size_t maximum = 0;
    size_t current = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isupper((unsigned char)*str) != 0) {
            ++current;
            if (current > maximum) {
                maximum = current;
            }
        } else {
            current = 0;
        }
        ++str;
    }

    return maximum;
}

int main(void)
{
    size_t maximum = 0;
    size_t current = 0;
    unsigned char *buffer = malloc(BUFSIZ);

    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        size_t count = fread(buffer, 1, BUFSIZ, stdin);

        for (size_t i = 0; i < count; ++i) {
            if (isupper(buffer[i]) != 0) {
                ++current;
                if (current > maximum) {
                    maximum = current;
                }
            } else {
                current = 0;
            }
        }

        if (count < BUFSIZ) {
            if (ferror(stdin) != 0) {
                free(buffer);
                return EXIT_FAILURE;
            }
            break;
        }
    }

    free(buffer);

    if (printf("%zu\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}