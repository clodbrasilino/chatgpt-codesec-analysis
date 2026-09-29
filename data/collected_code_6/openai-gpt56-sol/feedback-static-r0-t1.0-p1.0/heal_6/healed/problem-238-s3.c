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
    char input[INPUT_CAPACITY];
    size_t length = 0U;
    uint64_t count;
    int ch;

    while (length + 1U < sizeof input) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (length + 1U == sizeof input) {
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return 1;
        }

        if (ferror(stdin)) {
            return 1;
        }
    }

    input[length] = '\0';

    if (count_non_empty_substrings(length, &count) != 0) {
        return 1;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return 1;
    }

    return 0;
}