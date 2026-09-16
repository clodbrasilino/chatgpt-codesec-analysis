#include <stdio.h>
#include <string.h>
#include <stddef.h>

char *find_last_occurrence(char *str, int ch)
{
    char *last = NULL;
    char *current;

    if (str == NULL)
    {
        return NULL;
    }

    current = str;
    while (*current != '\0')
    {
        if (*current == (char)ch)
        {
            last = current;
        }
        current++;
    }

    if (ch == '\0')
    {
        return current;
    }

    return last;
}

int main(void)
{
    char test_string[] = "Hello, World!";
    char target = 'o';
    char *result;

    result = find_last_occurrence(test_string, target);

    if (result != NULL)
    {
        printf("Last occurrence of '%c' found at position: %ld\n", 
               target, (long)(result - test_string));
        printf("Character: %c\n", *result);
    }
    else
    {
        printf("Character '%c' not found in string.\n", target);
    }

    return 0;
}