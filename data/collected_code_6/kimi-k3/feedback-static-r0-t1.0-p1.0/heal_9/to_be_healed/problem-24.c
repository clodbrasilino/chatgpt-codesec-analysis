#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

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

    for (i = 0; binary[i] != '\0'; i++)
    {
        if (i >= MAX_BINARY_DIGITS)
        {
            return false;
        }

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
    char input[INPUT_BUFFER_SIZE];
    unsigned long long decimal;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);

    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
    }
    else if (len == sizeof(input) - 1)
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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