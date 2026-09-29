#include <stdio.h>
#include <stddef.h>

#define BUFFER_SIZE 256

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

void strip_newline(char *str, size_t max_len)
{
    size_t i = 0;

    if (str == NULL)
    {
        return;
    }

    while (i < max_len && str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t length;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    strip_newline(buffer, sizeof(buffer));

    length = count_characters(buffer);

    printf("%zu\n", length);

    return 0;
}