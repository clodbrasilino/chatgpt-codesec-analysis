#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

bool binary_to_decimal(const char *binary, unsigned long long *result)
{
    if (binary == NULL || result == NULL || *binary == '\0')
    {
        return false;
    }

    unsigned long long value = 0;
    size_t i;
    size_t length = strlen(binary);

    if (length > 64)
    {
        return false;
    }

    for (i = 0; i < length; i++)
    {
        if (binary[i] != '0' && binary[i] != '1')
        {
            return false;
        }

        if (value > (ULLONG_MAX >> 1))
        {
            return false;
        }

        value = (value << 1) | (unsigned long long)(binary[i] - '0');
    }

    *result = value;
    return true;
}

int main(void)
{
    char input[67];
    unsigned long long decimal;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return 1;
    }

    len = strcspn(input, "\n");
    if (len == 0 || len > 64)
    {
        fprintf(stderr, "Invalid binary number\n");
        return 1;
    }
    input[len] = '\0';

    if (binary_to_decimal(input, &decimal))
    {
        printf("%llu\n", decimal);
    }
    else
    {
        fprintf(stderr, "Invalid binary number\n");
        return 1;
    }

    return 0;
}