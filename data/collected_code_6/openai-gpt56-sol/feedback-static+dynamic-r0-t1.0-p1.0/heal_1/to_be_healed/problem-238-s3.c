#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

static int count_non_empty_substrings(const char *str, uint64_t *count)
{
    if (str == NULL || count == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);
    uint64_t n = (uint64_t)length;

    if (length != (size_t)n) {
        return -1;
    }

    if ((n & 1U) == 0U) {
        n /= 2U;
    } else {
        if (n == UINT64_MAX) {
            return -1;
        }
        n = (n + 1U) / 2U;
    }

    uint64_t factor = ((uint64_t)length & 1U) == 0U
                          ? (uint64_t)length + 1U
                          : (uint64_t)length;

    if (factor != 0U && n > UINT64_MAX / factor) {
        return -1;
    }

    *count = n * factor;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[length - 1U] = '\0';
    } else if (!feof(stdin)) {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 1;
    }

    uint64_t count;

    if (count_non_empty_substrings(input, &count) != 0) {
        return 1;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return 1;
    }

    return 0;
}