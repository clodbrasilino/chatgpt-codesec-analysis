#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int count_vowels(const char *str)
{
    int count = 0;

    if (str == NULL)
    {
        return 0;
    }

    while (*str != '\0')
    {
        int c = tolower((unsigned char)*str);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
            count++;
        }
        str++;
    }

    return count;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;
    int result;

    printf("Enter a string: ");

    line_length = getline(&buffer, &buffer_size, stdin);

    if (line_length == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    if (line_length > 0 && buffer[line_length - 1] == '\n')
    {
        buffer[line_length - 1] = '\0';
    }

    result = count_vowels(buffer);
    printf("Number of vowels: %d\n", result);

    free(buffer);
    return 0;
}