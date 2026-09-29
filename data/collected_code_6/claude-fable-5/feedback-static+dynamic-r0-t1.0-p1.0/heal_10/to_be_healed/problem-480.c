#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

#define INPUT_SIZE 256

int find_max_occurring_char(const char *str, char *result)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t i;
    unsigned char max_char = 0;
    int found = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
            max_char = c;
            found = 1;
        }
    }

    if (found == 0) {
        return -1;
    }

    *result = (char)max_char;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    char max_char;
    size_t len;

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (find_max_occurring_char(input, &max_char) != 0) {
        fprintf(stderr, "Empty string or invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum occurring character: %c\n", max_char) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}