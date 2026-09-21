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
        if (frequencies[data[i]] == SIZE_MAX) {
            return -1;
        }
        ++frequencies[data[i]];
    }

    return 0;
}

int main(void)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        if (bytes_read > 0 &&
            count_character_frequency(buffer, bytes_read, frequencies) != 0) {
            fprintf(stderr, "Failed to count character frequencies.\n");
            return EXIT_FAILURE;
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                fprintf(stderr, "Failed to read input.\n");
                return EXIT_FAILURE;
            }
            break;
        }
    }

    for (size_t i = 0; i < UCHAR_MAX + 1U; ++i) {
        if (frequencies[i] != 0) {
            printf("0x%02zX: %zu\n", i, frequencies[i]);
        }
    }

    return EXIT_SUCCESS;
}