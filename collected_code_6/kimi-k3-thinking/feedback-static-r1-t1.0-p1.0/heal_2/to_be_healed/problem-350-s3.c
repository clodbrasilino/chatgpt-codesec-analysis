#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

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

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i = 0;

    if (str == NULL)
    {
        return 0;
    }

    while (i < max_len && str[i] != '\0')
    {
        i++;
    }

    return i;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE] = {0};
    size_t len;
    size_t result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = bounded_strlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    }

    result = minimize_length(buffer);
    printf("%zu\n", result);

    return 0;
}