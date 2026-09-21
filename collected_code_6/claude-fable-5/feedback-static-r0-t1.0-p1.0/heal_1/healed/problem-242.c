#include <stdio.h>
#include <stddef.h>

size_t count_characters(const char *str)
{
    size_t count = 0;

    if (str == NULL)
    {
        return 0;
    }

    while (str[count] != '\0')
    {
        count++;
    }

    return count;
}

void strip_newline(char *str)
{
    size_t i = 0;

    if (str == NULL)
    {
        return;
    }

    while (str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            return;
        }
        i++;
    }
}

int main(void)
{
    char buffer[256];
    size_t length;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    strip_newline(buffer);

    length = count_characters(buffer);

    printf("Total characters: %zu\n", length);

    return 0;
}