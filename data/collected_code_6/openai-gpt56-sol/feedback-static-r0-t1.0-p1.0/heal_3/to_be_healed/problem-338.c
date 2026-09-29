#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#define INPUT_CAPACITY 4096U

static int count_substrings(const char *str, uint64_t *result)
{
    uint64_t frequencies[UCHAR_MAX + 1U] = {0};
    uint64_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; str[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)str[i];

        if (frequencies[c] == UINT64_MAX) {
            return -1;
        }

        uint64_t increment = frequencies[c] + UINT64_C(1);

        if (total > UINT64_MAX - increment) {
            return -1;
        }

        total += increment;
        ++frequencies[c];
    }

    *result = total;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];
    size_t length = 0;
    uint64_t result;
    int ch = EOF;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length >= sizeof input - 1U) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n');

            if (ferror(stdin)) {
                return 1;
            }

            return 1;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (ch == EOF && length == 0U) {
        return 1;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    input[length] = '\0';

    if (count_substrings(input, &result) != 0) {
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}