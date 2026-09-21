#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    long parsed;

    if (value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtol(line, &end, 10);

    if (end == line || errno == ERANGE) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = parsed;
    free(line);
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