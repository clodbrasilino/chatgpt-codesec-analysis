#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_spaces(const char* str, char replacement)
{
    char* new_str;
    size_t len;
    size_t i;
    
    if (str == NULL)
    {
        return NULL;
    }
    
    len = strlen(str);
    new_str = (char*)malloc(len + 1);
    
    if (new_str == NULL)
    {
        return NULL;
    }
    
    for (i = 0; i < len; i++)
    {
        if (str[i] == ' ')
        {
            new_str[i] = replacement;
        }
        else
        {
            new_str[i] = str[i];
        }
    }
    new_str[len] = '\0';
    
    return new_str;
}

int main(void)
{
    char* result;
    const char* test_string = "Hello World Example";
    char replacement = '_';
    
    result = replace_spaces(test_string, replacement);
    
    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Original: %s\n", test_string);
    printf("Modified: %s\n", result);
    
    free(result);
    
    return EXIT_SUCCESS;
}