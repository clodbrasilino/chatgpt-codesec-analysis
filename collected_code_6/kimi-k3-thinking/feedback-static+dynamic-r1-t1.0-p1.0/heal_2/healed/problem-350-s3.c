#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

size_t minimize_length(const char *str)
{
    size_t freq[256] = {0};
    size_t max_freq = 0;
    size_t len = 0;
    size_t i;

    if (str == NULL)
    {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++)
    {
        freq[(unsigned char)str[i]]++;
    }

    len = i;

    for (i = 0; i < 256; i++)
    {
        if (freq[i] > max_freq)
        {
            max_freq = freq[i];
        }
    }

    return len - max_freq;
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    ssize_t nread;
    size_t len;
    size_t result;

    nread = getline(&buffer, &capacity, stdin);
    if (nread < 0)
    {
        free(buffer);
        return 1;
    }

    len = (size_t)nread;
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    result = minimize_length(buffer);
    printf("%zu\n", result);

    free(buffer);

    return 0;
}