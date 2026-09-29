#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int count_character_frequency(const char *str, size_t frequencies[UCHAR_MAX + 1])
{
    if (str == NULL || frequencies == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        frequencies[i] = 0;
    }

    while (*str != '\0') {
        unsigned char character = (unsigned char)*str;
        ++frequencies[character];
        ++str;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[4096];
    size_t frequencies[UCHAR_MAX + 1];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (count_character_frequency(input, frequencies) != 0) {
        fprintf(stderr, "Failed to count character frequencies.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] != 0) {
            printf("0x%02zX: %zu\n", i, frequencies[i]);
        }
    }

    return EXIT_SUCCESS;
}