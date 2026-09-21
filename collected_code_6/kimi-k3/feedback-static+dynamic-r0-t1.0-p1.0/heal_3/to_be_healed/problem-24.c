#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool binary_to_decimal(const char *binary, unsigned long long *result)
{
    if (binary == NULL || result == NULL || *binary == '\0')
    {
        return false;
    }

    unsigned long long value = 0;
    size_t i;

    for (i = 0; binary[i] != '\0'; i++)
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[65];
    unsigned long long decimal;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

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