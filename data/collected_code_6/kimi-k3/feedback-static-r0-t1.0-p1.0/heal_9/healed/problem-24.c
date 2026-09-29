#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_BINARY_DIGITS 64
#define INPUT_BUFFER_SIZE (MAX_BINARY_DIGITS + 2)

bool binary_to_decimal(const char *binary, unsigned long long *result)
{
    if (binary == NULL || result == NULL || *binary == '\0')
    {
        return false;
    }

    unsigned long long value = 0;
    size_t i;
    size_t len = 0;

    while (binary[len] != '\0')
    {
        if (len >= MAX_BINARY_DIGITS)
        {
            return false;
        }
        len++;
    }

    for (i = 0; i < len; i++)
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
    char input[INPUT_BUFFER_SIZE];
    unsigned long long decimal;
    size_t len;
    int c;
    bool discard_needed = false;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return 1;
    }

    len = strnlen(input, sizeof(input));

    if (len == sizeof(input))
    {
        discard_needed = true;
    }
    else if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
        len--;
    }
    else if (len == sizeof(input) - 1)
    {
        discard_needed = true;
    }

    if (discard_needed)
    {
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        fprintf(stderr, "Invalid binary number\n");
        return 1;
    }

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