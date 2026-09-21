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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t count;

    while ((count = fread(buffer, sizeof buffer[0], sizeof buffer, stdin)) > 0) {
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
    }

    if (ferror(stdin) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}