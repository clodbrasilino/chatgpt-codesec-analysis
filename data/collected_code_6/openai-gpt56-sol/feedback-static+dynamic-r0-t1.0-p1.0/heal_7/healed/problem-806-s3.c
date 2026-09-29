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
        unsigned char ch = (unsigned char)*str++;

        if (isupper(ch)) {
            ++current;
            if (current > maximum) {
                maximum = current;
            }
        } else {
            current = 0;
        }
    }

    return maximum;
}

int main(void)
{
    char buffer[4096];
    size_t maximum = 0;
    size_t current = 0;

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        for (const unsigned char *p = (const unsigned char *)buffer;
             *p != '\0';
             ++p) {
            if (isupper(*p)) {
                ++current;
                if (current > maximum) {
                    maximum = current;
                }
            } else {
                current = 0;
            }
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}