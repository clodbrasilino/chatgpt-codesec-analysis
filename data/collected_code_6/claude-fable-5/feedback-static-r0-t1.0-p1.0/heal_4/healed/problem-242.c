#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define BUFFER_SIZE 256

size_t count_characters(const char *str)
{
    size_t count = 0;

    if (str == NULL)
    {
        return 0;
    }

    while (count < BUFFER_SIZE && str[count] != '\0')
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

    while (i < BUFFER_SIZE && str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            return;
        }
        i++;
    }
}

static void flush_stdin(void)
{
    size_t guard = 0;

    while (guard < (size_t)-1)
    {
        int ch = getchar();
        if (ch == '\n' || ch == EOF)
        {
            break;
        }
        guard++;
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t length;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    if (memchr(buffer, '\n', sizeof(buffer)) == NULL)
    {
        flush_stdin();
    }

    strip_newline(buffer);

    length = count_characters(buffer);

    printf("Total characters: %zu\n", length);

    return 0;
}