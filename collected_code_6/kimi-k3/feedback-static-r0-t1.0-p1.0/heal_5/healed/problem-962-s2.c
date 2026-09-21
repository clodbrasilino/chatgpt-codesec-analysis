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
    char buffer[256];
    char *p = buffer;
    char *end;
    intmax_t v1, v2;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    errno = 0;
    v1 = strtoimax(p, &end, 10);
    if (errno == ERANGE || end == p || v1 < INT64_MIN || v1 > INT64_MAX)
    {
        return 1;
    }
    p = end;

    errno = 0;
    v2 = strtoimax(p, &end, 10);
    if (errno == ERANGE || end == p || v2 < INT64_MIN || v2 > INT64_MAX)
    {
        return 1;
    }

    l = (int64_t)v1;
    r = (int64_t)v2;

    printf("%" PRId64 "\n", sum_even_natural(l, r));
    return 0;
}