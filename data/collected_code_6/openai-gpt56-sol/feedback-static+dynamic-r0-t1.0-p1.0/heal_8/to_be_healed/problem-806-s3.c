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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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