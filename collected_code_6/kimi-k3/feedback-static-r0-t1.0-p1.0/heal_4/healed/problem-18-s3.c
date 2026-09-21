#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_chars(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return NULL;
    }

    size_t len1 = strnlen(str1, 256);
    char *result = (char *)malloc(len1 + 1);
    if (result == NULL)
    {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len1; i++)
    {
        if (strchr(str2, str1[i]) == NULL)
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
    ssize_t len1, len2;

    printf("Enter first string: ");
    len1 = getline(&str1, &size1, stdin);
    if (len1 == -1)
    {
        fprintf(stderr, "Error reading input.\n");
        free(str1);
        return EXIT_FAILURE;
    }
    if (len1 > 0 && str1[len1 - 1] == '\n')
    {
        str1[len1 - 1] = '\0';
    }

    printf("Enter second string: ");
    len2 = getline(&str2, &size2, stdin);
    if (len2 == -1)
    {
        fprintf(stderr, "Error reading input.\n");
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }
    if (len2 > 0 && str2[len2 - 1] == '\n')
    {
        str2[len2 - 1] = '\0';
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