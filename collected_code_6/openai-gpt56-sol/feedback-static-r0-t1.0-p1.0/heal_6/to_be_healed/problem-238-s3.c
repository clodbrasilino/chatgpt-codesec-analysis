#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

#define INPUT_CAPACITY 4096U

static int count_non_empty_substrings(size_t length, uint64_t *count)
{
    uint64_t len;
    uint64_t first;
    uint64_t second;

    if (count == NULL) {
        return -1;
    }

#if SIZE_MAX > UINT64_MAX
    if (length > UINT64_MAX) {
        return -1;
    }
#endif

    len = (uint64_t)length;

    if ((len & UINT64_C(1)) == 0U) {
        first = len / UINT64_C(2);
        second = len + UINT64_C(1);
    } else {
        first = len;
        second = (len / UINT64_C(2)) + UINT64_C(1);
    }

    if (first != UINT64_C(0) && second > UINT64_MAX / first) {
        return -1;
    }

    *count = first * second;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];
    size_t length;
    uint64_t count;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    for (length = 0U; length < sizeof input && input[length] != '\0'; ++length) {
        if (input[length] == '\n') {
            break;
        }
    }

    if (length == sizeof input) {
        return 1;
    }

    if (input[length] == '\n') {
        /* Possible weaknesses found:
         *  Variable 'input[length]' is assigned a value that is never used. [unreadVariable]
         */
        input[length] = '\0';
    } else if (!feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return 1;
        }

        if (ferror(stdin)) {
            return 1;
        }
    }

    if (count_non_empty_substrings(length, &count) != 0) {
        return 1;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return 1;
    }

    return 0;
}