#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

unsigned long long count_substrings(const char *str, size_t max_len)
{
    unsigned long long n;

    if (str == NULL)
    {
        return 0ULL;
    }

    n = (unsigned long long)strnlen(str, max_len);

    if ((n % 2ULL) == 0ULL)
    {
        return (n / 2ULL) * (n + 1ULL);
    }

    return n * ((n + 1ULL) / 2ULL);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    unsigned long long result;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n')
    {
        buffer[len - 1U] = '\0';
    }

    result = count_substrings(buffer, sizeof(buffer));

    if (printf("%llu\n", result) < 0)
    {
        return 1;
    }

    return 0;
}