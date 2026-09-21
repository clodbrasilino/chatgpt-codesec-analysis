#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

static size_t safe_strnlen(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL)
    {
        return 0;
    }

    for (i = 0; i < max_len; i++)
    {
        if (str[i] == '\0')
        {
            break;
        }
    }

    return i;
}

unsigned long count_substrings(const char *str, size_t max_len)
{
    unsigned long freq[256] = {0};
    unsigned long total = 0;
    size_t i;
    size_t len;

    if (str == NULL)
    {
        return 0;
    }

    len = safe_strnlen(str, max_len);

    for (i = 0; i < len; i++)
    {
        freq[(unsigned char)str[i]]++;
    }

    for (i = 0; i < 256; i++)
    {
        total += (freq[i] * (freq[i] + 1)) / 2;
    }

    return total;
}

int main(void)
{
    char buffer[MAX_INPUT_SIZE];
    unsigned long result;
    size_t len;
    char *newline;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    newline = memchr(buffer, '\n', sizeof(buffer));
    if (newline != NULL)
    {
        *newline = '\0';
    }

    len = safe_strnlen(buffer, sizeof(buffer));
    if (len >= sizeof(buffer))
    {
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    result = count_substrings(buffer, sizeof(buffer));

    if (printf("%lu\n", result) < 0)
    {
        return 1;
    }

    return 0;
}