#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int binary_tuple_to_int(const char *binary_str, size_t length, int *result)
{
    int value;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
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
    /* Possible weaknesses found:
     *  Assignment 'binary_input="1011"', assigned value is "1011"
     */
    const char *binary_input = "1011";
    size_t length;
    int result;
    int status;

    /* Possible weaknesses found:
     *  Condition 'binary_input==NULL' is always false [knownConditionTrueFalse]
     *  Condition 'binary_input==NULL' is always false
     */
    if (binary_input == NULL)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assignment 'length=strlen(binary_input)', assigned value is 4
     */
    length = strlen(binary_input);

    /* Possible weaknesses found:
     *  Condition 'length==0' is always false
     *  Condition 'length==0' is always false [knownConditionTrueFalse]
     */
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