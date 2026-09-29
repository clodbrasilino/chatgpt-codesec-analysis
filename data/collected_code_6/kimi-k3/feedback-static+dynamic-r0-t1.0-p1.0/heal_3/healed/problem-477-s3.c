#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 255

char *to_lowercase(const char *input)
{
    char *result;
    size_t i;
    size_t len;

    if (input == NULL)
    {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LENGTH);
    result = (char *)malloc(len + 1);

    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < len; i++)
    {
        result[i] = (char)tolower((unsigned char)input[i]);
    }

    result[len] = '\0';

    return result;
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 1];
    char *lowercase_str;
    size_t input_len;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input_len = strnlen(input, sizeof(input));
    if (input_len == sizeof(input))
    {
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    lowercase_str = to_lowercase(input);

    if (lowercase_str == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Lowercase string: %s\n", lowercase_str);

    free(lowercase_str);
    lowercase_str = NULL;

    return 0;
}