#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got <no output>
  *  test case 0 failed: expected 'python', got <no output>
  *  test case 1 failed: expected 'string', got <no output>
  */

char *remove_parentheses(const char *str)
{
    char *result;
    size_t i;
    size_t j;
    int depth;

    if (str == NULL)
    {
        return NULL;
    }

    result = (char *)malloc(strlen(str) + 1);
    if (result == NULL)
    {
        return NULL;
    }

    j = 0;
    depth = 0;
    for (i = 0; str[i] != '\0'; i++)
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
    const char *input = "hello (world) this is (a (nested) test) string";
    char *output;

    output = remove_parentheses(input);
    if (output == NULL)
    {
        fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}