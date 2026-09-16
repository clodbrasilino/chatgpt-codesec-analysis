#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_parentheses(const char *str)
{
    char *result;
    size_t i;
    size_t j;
    size_t k;
    size_t len;

    if (str == NULL)
    {
        return NULL;
    }

    len = strlen(str);
    result = (char *)malloc(len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    i = 0;
    j = 0;
    while (i < len)
    {
        if (str[i] == '(')
        {
            k = i + 1;
            while (k < len && str[k] != '(' && str[k] != ')')
            {
                k++;
            }
            if (k < len && str[k] == ')')
            {
                if (j > 0 && isspace((unsigned char)result[j - 1]))
                {
                    j--;
                }
                i = k + 1;
            }
            else
            {
                result[j] = str[i];
                j++;
                i++;
            }
        }
        else
        {
            result[j] = str[i];
            j++;
            i++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(int argc, const char *argv[])
{
    char buffer[4096];
    const char *input;
    char *output;
    size_t len;

    input = NULL;

    if (argc > 1)
    {
        input = argv[1];
    }
    else if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r'))
        {
            buffer[len - 1] = '\0';
            len--;
        }
        input = buffer;
    }

    if (input == NULL)
    {
        fprintf(stderr, "Error: no input provided\n");
        return EXIT_FAILURE;
    }

    output = remove_parentheses(input);
    if (output == NULL)
    {
        fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}