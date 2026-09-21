#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    long first;
    long second;
} Tuple;

static Tuple maximize_tuples(Tuple left, Tuple right)
{
    Tuple result = {
        .first = left.first > right.first ? left.first : right.first,
        .second = left.second > right.second ? left.second : right.second
    };

    return result;
}

static int read_long(long *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end = NULL;
    long parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtol(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
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