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
    char *input = NULL;
    size_t input_size = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    unsigned long long decimal;

    read = getline(&input, &input_size, stdin);
    
    if (read == -1)
    {
        free(input);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && input[read - 1] == '\n')
    {
        input[read - 1] = '\0';
    }

    if (binary_to_decimal(input, &decimal))
    {
        printf("%llu\n", decimal);
        free(input);
    }
    else
    {
        fprintf(stderr, "Invalid binary number\n");
        free(input);
        return 1;
    }

    return 0;
}