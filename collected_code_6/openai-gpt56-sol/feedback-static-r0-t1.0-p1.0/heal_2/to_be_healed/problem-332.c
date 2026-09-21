#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int count_character_frequency(
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const unsigned char *data,
    size_t length,
    size_t frequencies[static UCHAR_MAX + 1])
{
    if (data == NULL || frequencies == NULL) {
        return -1;
    }

    for (size_t i = 0; i < UCHAR_MAX + 1U; ++i) {
        frequencies[i] = 0;
    }

    for (size_t i = 0; i < length; ++i) {
        ++frequencies[data[i]];
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[4096];
    size_t frequencies[UCHAR_MAX + 1];

    size_t length = fread(input, 1, sizeof input, stdin);
    if (ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (count_character_frequency(input, length, frequencies) != 0) {
        fprintf(stderr, "Failed to count character frequencies.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < UCHAR_MAX + 1U; ++i) {
        if (frequencies[i] != 0) {
            printf("0x%02zX: %zu\n", i, frequencies[i]);
        }
    }

    return EXIT_SUCCESS;
}