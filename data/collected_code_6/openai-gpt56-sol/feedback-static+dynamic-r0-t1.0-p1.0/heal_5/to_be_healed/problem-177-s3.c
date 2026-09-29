#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int find_numbers(long long left, long long right,
                        long long *first, long long *second)
{
    if (first == NULL || second == NULL || left < 1 || right < left) {
        return 0;
    }

    if (left <= right / 2) {
        *first = left;
        *second = left * 2;
        return 1;
    }

    return 0;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end;
    long long result;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    result = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = result;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    long long left;
    long long right;
    long long first;
    long long second;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower_bound> <upper_bound>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_long_long(argv[1], &left) ||
        !parse_long_long(argv[2], &right) ||
        left < 1 || right < left) {
        fprintf(stderr, "Invalid range\n");
        return EXIT_FAILURE;
    }

    if (!find_numbers(left, right, &first, &second)) {
        puts("-1");
        return EXIT_SUCCESS;
    }

    printf("%lld %lld\n", first, second);
    return EXIT_SUCCESS;
}