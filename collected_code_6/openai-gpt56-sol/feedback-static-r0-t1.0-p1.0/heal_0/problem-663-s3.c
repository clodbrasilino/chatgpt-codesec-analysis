#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int largest_k(int x, int y, int upper_bound, int *result)
{
    if (result == NULL || x <= 0 || y < 0 || y >= x || upper_bound < y) {
        return 0;
    }

    *result = upper_bound - ((upper_bound - y) % x);
    return 1;
}

static int parse_int(const char *text, int *value)
{
    char *end = NULL;
    long parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int main(int argc, char *argv[])
{
    int x;
    int y;
    int upper_bound;
    int result;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <x> <y> <upper_bound>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_int(argv[1], &x) ||
        !parse_int(argv[2], &y) ||
        !parse_int(argv[3], &upper_bound)) {
        fputs("Invalid integer input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!largest_k(x, y, upper_bound, &result)) {
        fputs("Require x > 0, 0 <= y < x, and upper_bound >= y.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}