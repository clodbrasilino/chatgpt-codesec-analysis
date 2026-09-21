#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static int nonagonal_number(uint64_t n, uint64_t *result)
{
    if (result == NULL)
    {
        return -1;
    }

    if (n == 0)
    {
        *result = 0;
        return 0;
    }

    uint64_t n_minus_1 = n - 1;

    if (n > UINT64_MAX / 7)
    {
        return -1;
    }
    uint64_t term1 = 7 * n;

    if (n_minus_1 > UINT64_MAX / 5)
    {
        return -1;
    }
    uint64_t term2 = 5 * n_minus_1;

    if (term1 < term2)
    {
        return -1;
    }
    uint64_t diff = term1 - term2;

    if (diff % 2 != 0)
    {
        return -1;
    }

    *result = diff / 2;
    return 0;
}

static int safe_read_line(char *buffer, size_t size, FILE *stream)
{
    if (buffer == NULL || size == 0 || stream == NULL)
    {
        return -1;
    }

    if (fgets(buffer, size, stream) == NULL)
    {
        return -1;
    }

    size_t len = strnlen(buffer, size);
    if (len == 0 || len == size)
    {
        return -1;
    }

    if (buffer[len - 1] != '\n')
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = fgetc(stream)) != EOF && c != '\n')
        {
        }
        return -1;
    }

    buffer[len - 1] = '\0';
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t result;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;

    printf("Enter n: ");

    if (safe_read_line(buffer, sizeof(buffer), stdin) != 0)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    n = strtoull(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\0')
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (nonagonal_number(n, &result) != 0)
    {
        fprintf(stderr, "Overflow or calculation error\n");
        return 1;
    }

    printf("The %" PRIu64 "th nonagonal number is: %" PRIu64 "\n", n, result);

    return 0;
}