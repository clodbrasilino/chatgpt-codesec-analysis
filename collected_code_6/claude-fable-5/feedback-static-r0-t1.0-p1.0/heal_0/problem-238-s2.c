#include <stdio.h>
#include <string.h>

unsigned long long count_substrings(const char *str)
{
    unsigned long long n;

    if (str == NULL)
    {
        return 0ULL;
    }

    n = (unsigned long long)strlen(str);

    return (n * (n + 1ULL)) / 2ULL;
}

int main(void)
{
    char buffer[1024];
    unsigned long long result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strlen(buffer);
    if (len > 0U && buffer[len - 1U] == '\n')
    {
        buffer[len - 1U] = '\0';
    }

    result = count_substrings(buffer);

    if (printf("%llu\n", result) < 0)
    {
        return 1;
    }

    return 0;
}