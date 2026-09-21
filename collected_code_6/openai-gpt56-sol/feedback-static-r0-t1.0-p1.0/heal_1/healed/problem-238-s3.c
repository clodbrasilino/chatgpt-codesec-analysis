#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define INPUT_CAPACITY 4096U

static int count_non_empty_substrings(size_t length, uint64_t *count)
{
    if (count == NULL || length > UINT64_MAX) {
        return -1;
    }

    uint64_t len = (uint64_t)length;
    uint64_t first;
    uint64_t second;

    if ((len & UINT64_C(1)) == 0U) {
        first = len / UINT64_C(2);
        second = len + UINT64_C(1);
    } else {
        first = len;
        second = (len / UINT64_C(2)) + UINT64_C(1);
    }

    if (first != 0U && second > UINT64_MAX / first) {
        return -1;
    }

    *count = first * second;
    return 0;
}

int main(void)
{
    char input[INPUT_CAPACITY];
    size_t length = 0U;
    int ch = 0;
    int too_long = 0;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1U < sizeof input) {
            input[length++] = (char)ch;
        } else {
            too_long = 1;
        }
    }

    if (ferror(stdin) || too_long) {
        return 1;
    }

    if (ch == EOF && length == 0U) {
        return 1;
    }

    input[length] = '\0';

    uint64_t count = 0U;

    if (count_non_empty_substrings(length, &count) != 0) {
        return 1;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return 1;
    }

    return 0;
}