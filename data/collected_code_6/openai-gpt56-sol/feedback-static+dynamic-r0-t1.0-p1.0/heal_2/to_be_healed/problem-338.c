#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int count_substrings(const char *str, size_t length, uint64_t *result)
{
    uint64_t frequencies[256] = {0};
    uint64_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char c = (unsigned char)str[i];

        if (frequencies[c] == UINT64_MAX ||
            total > UINT64_MAX - frequencies[c] - 1) {
            return -1;
        }

        total += frequencies[c] + 1;
        ++frequencies[c];
    }

    *result = total;
    return 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];
    size_t length = 0;
    uint64_t result;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == sizeof input) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n');
            return 1;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (ch == EOF && length == 0) {
        return 1;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    if (count_substrings(input, length, &result) != 0) {
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}