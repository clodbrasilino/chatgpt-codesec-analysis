#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *toggle_case(const char *str)
{
    if (str == NULL)
    {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);

    if (result == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < len; i++)
    {
        unsigned char c = (unsigned char)str[i];
        if (isupper(c))
        {
            result[i] = (char)tolower(c);
        }
        else if (islower(c))
        {
            result[i] = (char)toupper(c);
        }
        else
        {
            result[i] = (char)c;
        }
    }

    result[len] = '\0';
    return result;
}

int main(void)
{
    const char *input = "Hello World! 123";
    char *toggled = toggle_case(input);

    if (toggled == NULL)
    {
        fprintf(stderr, "Error: Failed to toggle case.\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Toggled:  %s\n", toggled);

    free(toggled);
    toggled = NULL;

    return EXIT_SUCCESS;
}