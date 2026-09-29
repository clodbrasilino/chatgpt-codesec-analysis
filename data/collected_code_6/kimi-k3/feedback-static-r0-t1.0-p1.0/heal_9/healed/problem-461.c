#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_uppercase(const char *str)
{
    int count = 0;
    if (str == NULL)
    {
        return 0;
    }
    while (*str != '\0')
    {
        if (isupper((unsigned char)*str))
        {
            count++;
        }
        str++;
    }
    return count;
}

int main(void)
{
    char buffer[256];
    int result;
    size_t len;
    int c;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    len = strcspn(buffer, "\n");

    if (len == sizeof(buffer) - 1 && buffer[len] == '\0')
    {
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    buffer[len] = '\0';

    result = count_uppercase(buffer);
    printf("Number of uppercase characters: %d\n", result);

    return 0;
}