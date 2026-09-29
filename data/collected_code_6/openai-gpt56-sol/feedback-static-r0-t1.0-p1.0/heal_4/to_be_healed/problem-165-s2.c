#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_matching_positions(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    for (size_t i = 0; i < 26 && str[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)str[i];

        if (tolower(ch) == 'a' + (int)i) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[27];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;

    while (length < sizeof input - 1 &&
           input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    input[length] = '\0';

    if (printf("%zu\n", count_matching_positions(input)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}