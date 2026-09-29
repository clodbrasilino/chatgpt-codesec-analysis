#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

char *remove_chars(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return NULL;
    }

    size_t len1 = strnlen(str1, MAX_INPUT_SIZE);
    char *result = (char *)malloc(len1 + 1);
    if (result == NULL)
    {
        return NULL;
    }

    size_t j = 0;
    size_t len2 = strnlen(str2, MAX_INPUT_SIZE);
    for (size_t i = 0; i < len1; i++)
    {
        int found = 0;
        for (size_t k = 0; k < len2; k++)
        {
            if (str1[i] == str2[k])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            result[j++] = str1[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char *str1 = NULL;
    char *str2 = NULL;
    size_t size1 = 0;
    size_t size2 = 0;
    ssize_t read1, read2;

    printf("Enter first string: ");
    read1 = getline(&str1, &size1, stdin);
    if (read1 == -1)
    {
        fprintf(stderr, "Error reading input.\n");
        free(str1);
        return EXIT_FAILURE;
    }
    if (read1 > 0 && str1[read1 - 1] == '\n')
    {
        str1[read1 - 1] = '\0';
    }

    printf("Enter second string: ");
    read2 = getline(&str2, &size2, stdin);
    if (read2 == -1)
    {
        fprintf(stderr, "Error reading input.\n");
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }
    if (read2 > 0 && str2[read2 - 1] == '\n')
    {
        str2[read2 - 1] = '\0';
    }

    char *result = remove_chars(str1, str2);
    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", result);

    free(result);
    free(str1);
    free(str2);

    return EXIT_SUCCESS;
}