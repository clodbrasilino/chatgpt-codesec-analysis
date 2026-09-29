#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

int64_t sum_even_natural(int64_t l, int64_t r)
{
    if (l > r || r < 2)
    {
        return 0;
    }

    if (l < 2)
    {
        l = 2;
    }

    int64_t first = (l % 2 == 0) ? l : l + 1;
    int64_t last = (r % 2 == 0) ? r : r - 1;

    if (first > last)
    {
        return 0;
    }

    int64_t count = (last - first) / 2 + 1;
    return count * (first + last) / 2;
}

int main(void)
{
    int64_t l, r;
    char *line = NULL;
    size_t line_size = 0;
    ssize_t line_length;
    char *p;
    char *end;
    intmax_t v1, v2;

    line_length = getline(&line, &line_size, stdin);
    if (line_length == -1)
    {
        free(line);
        return 1;
    }

    p = line;

    errno = 0;
    v1 = strtoimax(p, &end, 10);
    if (errno == ERANGE || end == p || v1 < INT64_MIN || v1 > INT64_MAX)
    {
        free(line);
        return 1;
    }
    p = end;

    errno = 0;
    v2 = strtoimax(p, &end, 10);
    if (errno == ERANGE || end == p || v2 < INT64_MIN || v2 > INT64_MAX)
    {
        free(line);
        return 1;
    }

    l = (int64_t)v1;
    r = (int64_t)v2;

    printf("%" PRId64 "\n", sum_even_natural(l, r));

    free(line);
    return 0;
}