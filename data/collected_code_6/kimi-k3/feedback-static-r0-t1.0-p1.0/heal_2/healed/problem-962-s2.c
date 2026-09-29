#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

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

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    if (sscanf(buffer, "%" SCNd64 " %" SCNd64, &l, &r) != 2)
    {
        return 1;
    }

    printf("%" PRId64 "\n", sum_even_natural(l, r));
    return 0;
}