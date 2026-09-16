#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *to_lower(const char *str)
{
    size_t len = 0;
    size_t i = 0;
    char *result = NULL;

    if (str == NULL)
    {
        return NULL;
    }

    while (str[len] != '\0')
    {
        len++;
    }

    result = (char *)malloc(len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < len; i++)
    {
        result[i] = (char)tolower((unsigned char)str[i]);
    }

    result[len] = '\0';

    return result;
}

int main(void)
{
    char *lower_str = NULL;
    const char *original = "HELLO WORLD 123!";

    lower_str = to_lower(original);
    if (lower_str != NULL)
    {
        printf("%s\n", lower_str);
        free(lower_str);
        lower_str = NULL;
    }

    lower_str = to_lower(NULL);
    if (lower_str == NULL)
    {
        printf("Handled NULL input successfully.\n");
    }

    return 0;
}