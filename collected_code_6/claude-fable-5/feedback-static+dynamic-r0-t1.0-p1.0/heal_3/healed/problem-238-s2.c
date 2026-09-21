#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char *buffer;
    unsigned long long result;
    size_t len;

    buffer = (char *)calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    buffer[BUFFER_SIZE - 1U] = '\0';

    len = strnlen(buffer, BUFFER_SIZE);
    if (len > 0U && buffer[len - 1U] == '\n')
    {
        buffer[len - 1U] = '\0';
    }

    result = count_substrings(buffer, BUFFER_SIZE);

    if (printf("%llu\n", result) < 0)
    {
        free(buffer);
        return 1;
    }

    free(buffer);
    return 0;
}