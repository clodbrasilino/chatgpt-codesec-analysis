#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int find_numbers(long long left, long long right,
                        long long *first, long long *second)
{
    if (first == NULL || second == NULL || left <= 0 || right < left) {
        return 0;
    }

    if (left <= right / 2) {
        *first = left;
        *second = left * 2;
        return 1;
    }

    return 0;
}

int main(void)
{
    char input[256];
    char *cursor;
    char *end;
    long long left;
    long long right;
    long long first;
    long long second;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    cursor = input;
    errno = 0;
    left = strtoll(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    cursor = end;
    errno = 0;
    right = strtoll(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (find_numbers(left, right, &first, &second)) {
        if (printf("%lld %lld\n", first, second) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("-1 -1\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}