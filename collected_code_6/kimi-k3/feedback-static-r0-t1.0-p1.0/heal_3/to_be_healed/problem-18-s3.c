#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_chars(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return NULL;
    }

    size_t len1 = strnlen(str1, 4096);
    char *result = (char *)malloc(len1 + 1);
    if (result == NULL)
    {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len1; i++)
    {
        int found = 0;
        for (size_t k = 0; k < 4096 && str2[k] != '\0'; k++)
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[256];

    printf("Enter first string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    str2[strcspn(str2, "\n")] = '\0';

    char *result = remove_chars(str1, str2);
    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}