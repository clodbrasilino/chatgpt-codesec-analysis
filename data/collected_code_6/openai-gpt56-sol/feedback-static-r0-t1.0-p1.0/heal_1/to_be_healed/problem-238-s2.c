#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int count_nonempty_substrings(const char *str, uintmax_t *count)
{
    size_t length;
    uintmax_t n;

    if (str == NULL || count == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(str);
    n = (uintmax_t)length;

    if (n != 0U && n + 1U > UINTMAX_MAX / n) {
        return -1;
    }

    *count = n * (n + 1U) / 2U;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[4096];
    uintmax_t count;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        input[0] = '\0';
    } else {
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

            if (ferror(stdin)) {
                return 1;
            }

            return 1;
        }
    }

    if (count_nonempty_substrings(input, &count) != 0) {
        return 1;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}