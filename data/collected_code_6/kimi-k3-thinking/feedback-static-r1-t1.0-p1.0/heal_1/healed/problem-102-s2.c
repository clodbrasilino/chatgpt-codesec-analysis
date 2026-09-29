#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SNAKE_TO_CAMEL_MAX_INPUT 4096U

char *snake_to_camel(const char *str)
{
    size_t len;
    size_t i;
    size_t j = 0;
    int upper_next = 0;
    char *result;

    if (str == NULL)
    {
        return NULL;
    }

    len = strnlen(str, SNAKE_TO_CAMEL_MAX_INPUT);
    if (len == SNAKE_TO_CAMEL_MAX_INPUT)
    {
        return NULL;
    }

    result = (char *)malloc(len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < len; i++)
    {
        if (str[i] == '_')
        {
            if (j > 0)
            {
                upper_next = 1;
            }
        }
        else
        {
            if (upper_next)
            {
                result[j] = (char)toupper((unsigned char)str[i]);
                j++;
                upper_next = 0;
            }
            else
            {
                result[j] = str[i];
                j++;
            }
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *inputs[] = {
        "hello_world",
        "snake_case_string_example",
        "convert_this_please",
        "already",
        "_leading_and_trailing_"
    };
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);
    size_t k;

    for (k = 0; k < num_inputs; k++)
    {
        char *output = snake_to_camel(inputs[k]);
        if (output == NULL)
        {
            fprintf(stderr, "Error: failed to convert \"%s\"\n", inputs[k]);
            return EXIT_FAILURE;
        }

        printf("Input:  %s\n", inputs[k]);
        printf("Output: %s\n\n", output);

        free(output);
        output = NULL;
    }

    return EXIT_SUCCESS;
}