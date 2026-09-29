#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

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

    int64_t first;
    int64_t last;

    if (l % 2 == 0)
    {
        first = l;
    }
    else
    {
        if (l == INT64_MAX)
        {
            return 0;
        }
        first = l + 1;
    }

    if (r % 2 == 0)
    {
        last = r;
    }
    else
    {
        if (r == INT64_MIN)
        {
            return 0;
        }
        last = r - 1;
    }

    if (first > last)
    {
        return 0;
    }

    uint64_t uf = (uint64_t)first;
    uint64_t ul = (uint64_t)last;
    uint64_t count = (ul - uf) / 2 + 1;
    uint64_t sum = uf + ul;
    uint64_t result;

    if (count % 2 == 0)
    {
        result = (count / 2) * sum;
    }
    else
    {
        result = count * (sum / 2);
    }

    return (int64_t)result;
}

static int parse_int64(const char *str, int64_t *out)
{
    char *endptr;
    intmax_t val;

    if (str == NULL || out == NULL)
    {
        return 0;
    }

    while (isspace((unsigned char)*str))
    {
        str++;
    }

    if (*str == '\0')
    {
        return 0;
    }

    errno = 0;
    val = strtoimax(str, &endptr, 10);

    if (endptr == str)
    {
        return 0;
    }

    if (errno == ERANGE)
    {
        return 0;
    }

    if (val < INT64_MIN || val > INT64_MAX)
    {
        return 0;
    }

    while (isspace((unsigned char)*endptr))
    {
        endptr++;
    }

    if (*endptr != '\0')
    {
        return 0;
    }

    *out = (int64_t)val;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[512];
    int64_t l, r;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin))
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        return 1;
    }

    if (!parse_int64(buffer, &l))
    {
        return 1;
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin))
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        return 1;
    }

    if (!parse_int64(buffer, &r))
    {
        return 1;
    }

    printf("%" PRId64 "\n", sum_even_natural(l, r));
    return 0;
}