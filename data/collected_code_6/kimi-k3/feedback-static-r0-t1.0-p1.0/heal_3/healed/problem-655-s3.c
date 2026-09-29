#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static uint64_t sum_fifth_powers(uint64_t n)
{
    uint64_t sum = 0;
    uint64_t i;

    for (i = 1; i <= n; ++i)
    {
        uint64_t square = i * i;
        uint64_t fifth = square * square * i;
        sum += fifth;
    }

    return sum;
}

int main(void)
{
    uint64_t n;
    char buffer[64];
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    errno = 0;
    n = strtoull(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\0')
    {
        return 1;
    }

    printf("%" PRIu64 "\n", sum_fifth_powers(n));

    return 0;
}