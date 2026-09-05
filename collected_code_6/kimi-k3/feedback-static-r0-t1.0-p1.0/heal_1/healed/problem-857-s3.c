#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*StringOperation)(const char *);

void print_string(const char *str)
{
    if (str != NULL)
    {
        printf("%s\n", str);
    }
}

void map_strings(char **strings, size_t count, StringOperation operation)
{
    size_t i;
    
    if (strings == NULL || operation == NULL || count == 0)
    {
        return;
    }
    
    for (i = 0; i < count; i++)
    {
        if (strings[i] != NULL)
        {
            operation(strings[i]);
        }
    }
}

int main(void)
{
    char *strings[] = {
        "Hello",
        "World",
        "This",
        "Is",
        "C",
        "Programming"
    };
    
    size_t count = sizeof(strings) / sizeof(strings[0]);
    
    map_strings(strings, count, print_string);
    
    return EXIT_SUCCESS;
}