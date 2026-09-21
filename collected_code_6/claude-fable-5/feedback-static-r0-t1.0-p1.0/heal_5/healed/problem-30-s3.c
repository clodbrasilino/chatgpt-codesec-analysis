#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

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

    len = strnlen(str, max_len);

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
    char buffer[BUFFER_SIZE];
    unsigned long result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    result = count_substrings(buffer, sizeof(buffer));

    if (printf("%lu\n", result) < 0)
    {
        return 1;
    }

    return 0;
}