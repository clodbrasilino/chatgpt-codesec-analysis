#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER_SIZE 1024

static unsigned long long count_substrings(const char *str, size_t max_len)
{
    unsigned long long n;

    if (str == NULL)
    {
        return 0ULL;
    }

    n = (unsigned long long)strnlen(str, max_len);

    if (n > 0ULL && n > (ULLONG_MAX / (n + 1ULL)))
    {
        return 0ULL;
    }

    return (n * (n + 1ULL)) / 2ULL;
}

int main(void)
{
    char *buffer;
    unsigned long long result;
    size_t len;

    buffer = (char *)calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[BUFFER_SIZE - 1] = '\0';

    len = strnlen(buffer, BUFFER_SIZE);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    result = count_substrings(buffer, BUFFER_SIZE);

    if (printf("%llu\n", result) < 0)
    {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}