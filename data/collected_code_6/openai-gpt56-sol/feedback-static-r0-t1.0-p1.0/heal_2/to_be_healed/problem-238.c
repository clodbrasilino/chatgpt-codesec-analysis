#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define INPUT_CAPACITY 4096U

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t n;

    if (count == NULL) {
        return 0;
    }

    n = (uintmax_t)length;

    if (n > 0 && n > (UINTMAX_MAX - 1U) / n) {
        return 0;
    }

    *count = n * (n + 1U) / 2U;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];
    size_t length = 0;
    uintmax_t count;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U >= sizeof input) {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            }
            return 1;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        return 1;
    }

    input[length] = '\0';

    if (!count_nonempty_substrings(length, &count)) {
        return 1;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}