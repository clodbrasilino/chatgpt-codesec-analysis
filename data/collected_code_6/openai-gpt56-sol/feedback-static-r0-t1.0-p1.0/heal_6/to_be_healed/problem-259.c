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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[sizeof(long) * CHAR_BIT + 4];
    char *end;
    long parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    size_t length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == 0 || length == sizeof buffer) {
        return 0;
    }

    if (buffer[length - 1] != '\n' && !feof(stdin)) {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
        return 0;
    }

    errno = 0;
    parsed = strtol(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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

    if (!read_long(&left.first) ||
        !read_long(&left.second) ||
        !read_long(&right.first) ||
        !read_long(&right.second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    Tuple result = maximize_tuples(left, right);

    if (printf("(%ld, %ld)\n", result.first, result.second) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}