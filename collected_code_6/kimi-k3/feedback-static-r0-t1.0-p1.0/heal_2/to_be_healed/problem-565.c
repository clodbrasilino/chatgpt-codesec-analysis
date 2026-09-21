#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string(const char *str, size_t *count)
{
    char **result;
    size_t len;
    size_t i;

    if (str == NULL || count == NULL)
    {
        return NULL;
    }

    len = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'len<1024' is not redundant
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (str[len] != '\0' && len < 1024)
    {
        len++;
    }

    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'len<1024' is redundant or the array 'str[6]' is accessed at index 1024, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    if (str[len] != '\0')
    {
        return NULL;
    }

    result = (char **)malloc((len + 1) * sizeof(char *));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < len; i++)
    {
        result[i] = (char *)malloc(2 * sizeof(char));
        if (result[i] == NULL)
        {
            size_t j;
            for (j = 0; j < i; j++)
            {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        result[i][0] = str[i];
        result[i][1] = '\0';
    }

    result[len] = NULL;
    *count = len;
    return result;
}

void free_split_string(char **arr, size_t count)
{
    size_t i;

    if (arr == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

int main(void)
{
    const char *input = "Hello";
    size_t count = 0;
    char **chars = split_string(input, &count);
    size_t i;

    if (chars == NULL)
    {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++)
    {
        printf("%s\n", chars[i]);
    }

    free_split_string(chars, count);
    return EXIT_SUCCESS;
}