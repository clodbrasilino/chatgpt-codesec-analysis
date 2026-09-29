#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int binary_to_decimal(const char *binary, unsigned long long *result)
{
    size_t len;
    size_t i;
    unsigned long long value = 0ULL;

    if (binary == NULL || result == NULL) {
        return -1;
    }

    len = strnlen(binary, 128U);
    if (len == 0U || len >= 128U) {
        return -1;
    }

    for (i = 0U; i < len; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            return -1;
        }
        if (value > (ULLONG_MAX >> 1)) {
            return -1;
        }
        value = (value << 1) | (unsigned long long)(binary[i] - '0');
    }

    *result = value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    unsigned long long decimal = 0ULL;
    size_t len;

    printf("Enter a binary number: ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1U] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0U && input[len - 1U] == '\n') {
        input[len - 1U] = '\0';
    } else {
        int ch;
        int truncated = 0;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            truncated = 1;
        }
        if (truncated == 1) {
            fprintf(stderr, "Error: input too long.\n");
            return EXIT_FAILURE;
        }
    }

    if (binary_to_decimal(input, &decimal) != 0) {
        fprintf(stderr, "Error: invalid binary number.\n");
        return EXIT_FAILURE;
    }

    printf("Decimal equivalent: %llu\n", decimal);
    return EXIT_SUCCESS;
}