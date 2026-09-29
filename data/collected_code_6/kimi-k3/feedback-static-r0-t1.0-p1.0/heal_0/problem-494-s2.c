#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int binary_tuple_to_int(const char *binary_str, size_t length, int *result)
{
    int value;
    size_t i;
    char c;

    if (binary_str == NULL || result == NULL || length == 0)
    {
        return -1;
    }

    if (length > (sizeof(int) * CHAR_BIT))
    {
        return -2;
    }

    value = 0;

    for (i = 0; i < length; i++)
    {
        c = binary_str[i];

        if (c != '0' && c != '1')
        {
            return -3;
        }

        if (value > (INT_MAX >> 1))
        {
            return -4;
        }

        value = (value << 1) | (c - '0');
    }

    *result = value;
    return 0;
}

int main(void)
{
    const char *binary_input = "1011";
    size_t length;
    int result;
    int status;

    if (binary_input == NULL)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    length = strlen(binary_input);

    if (length == 0)
    {
        fprintf(stderr, "Error: Empty input\n");
        return EXIT_FAILURE;
    }

    status = binary_tuple_to_int(binary_input, length, &result);

    if (status != 0)
    {
        fprintf(stderr, "Error: Conversion failed with code %d\n", status);
        return EXIT_FAILURE;
    }

    printf("Binary: %s\n", binary_input);
    printf("Integer: %d\n", result);

    return EXIT_SUCCESS;
}