#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 9
#define BUFFER_SIZE 64

int find_demlo(const char *input, char *output, size_t output_size)
{
    size_t len;
    size_t pos;
    size_t i;

    if (input == NULL || output == NULL || output_size == 0U)
    {
        return -1;
    }

    len = strnlen(input, (size_t)MAX_INPUT_LEN + 1U);

    if (len == 0U || len > MAX_INPUT_LEN)
    {
        return -1;
    }

    for (i = 0U; i < len; i++)
    {
        if (input[i] != '1')
        {
            return -1;
        }
    }

    if (output_size < (2U * len))
    {
        return -1;
    }

    pos = 0U;

    for (i = 1U; i <= len; i++)
    {
        output[pos] = (char)('0' + (char)i);
        pos++;
    }

    for (i = len; i > 1U; i--)
    {
        output[pos] = (char)('0' + (char)(i - 1U));
        pos++;
    }

    output[pos] = '\0';

    return 0;
}

int main(void)
{
    char input[BUFFER_SIZE];
    char result[BUFFER_SIZE];
    size_t len;

    printf("Enter a repunit number (only 1s, max %d digits): ", MAX_INPUT_LEN);

    if (fgets(input, (int)sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1U] = '\0';
    len = strnlen(input, sizeof(input));

    if (len > 0U && input[len - 1U] == '\n')
    {
        input[len - 1U] = '\0';
    }
    else
    {
        int c;
        do
        {
            c = getchar();
        } while (c != '\n' && c != EOF);
    }

    if (find_demlo(input, result, sizeof(result)) != 0)
    {
        fprintf(stderr, "Error: invalid input, expected 1 to %d ones\n", MAX_INPUT_LEN);
        return EXIT_FAILURE;
    }

    printf("Demlo number: %s\n", result);

    return EXIT_SUCCESS;
}