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
            if (depth == 1 && j > 0 && result[j - 1] == ' ')
            {
                j--;
            }
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
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