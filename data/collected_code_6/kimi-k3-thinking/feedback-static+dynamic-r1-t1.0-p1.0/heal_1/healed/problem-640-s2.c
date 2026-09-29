#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

char *remove_parentheses(const char *str)
{
    char *result;
    size_t i;
    size_t j;
    size_t len;
    int depth;

    if (str == NULL)
    {
        return NULL;
    }

    len = 0;
    while (len < MAX_STRING_LENGTH && str[len] != '\0')
    {
        len++;
    }

    if (str[len] != '\0')
    {
        return NULL;
    }

    result = (char *)malloc(len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    j = 0;
    depth = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] == '(')
        {
            depth++;
        }
        else if (str[i] == ')')
        {
            if (depth > 0)
            {
                depth--;
            }
        }
        else if (depth == 0)
        {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *inputs[] = {
        "hello (world) this is (a (nested) test) string",
        "python",
        "alpha",
        "string"
    };
    size_t k;
    char *output;

    for (k = 0; k < sizeof(inputs) / sizeof(inputs[0]); k++)
    {
        output = remove_parentheses(inputs[k]);
        if (output == NULL)
        {
            fprintf(stderr, "Error: failed to process string\n");
            return EXIT_FAILURE;
        }

        printf("Input:  %s\n", inputs[k]);
        printf("Output: %s\n", output);

        free(output);
        output = NULL;
    }

    return EXIT_SUCCESS;
}