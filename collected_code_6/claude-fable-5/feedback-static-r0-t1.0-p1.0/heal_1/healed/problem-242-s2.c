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

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t length;
    size_t i;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    i = 0;
    while (i < sizeof(buffer) && buffer[i] != '\0')
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            break;
        }
        i++;
    }

    length = count_characters(buffer);

    printf("Total characters: %zu\n", length);

    return 0;
}