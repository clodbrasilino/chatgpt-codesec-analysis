#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

typedef struct {
    long first;
    long second;
} Tuple;

static Tuple maximize_tuples(Tuple left, Tuple right)
{
    Tuple result = {
        left.first > right.first ? left.first : right.first,
        left.second > right.second ? left.second : right.second
    };

    return result;
}

static int read_long(long *value)
{
    char buffer[sizeof(long) * CHAR_BIT + 4];
    char *end;
    long parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtol(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    Tuple left;
    Tuple right;
    Tuple result;

    if (!read_long(&left.first) ||
        !read_long(&left.second) ||
        !read_long(&right.first) ||
        !read_long(&right.second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    result = maximize_tuples(left, right);

    if (printf("(%ld, %ld)\n", result.first, result.second) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}