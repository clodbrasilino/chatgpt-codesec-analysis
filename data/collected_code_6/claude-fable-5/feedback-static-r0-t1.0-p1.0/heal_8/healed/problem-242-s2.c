#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define BUFFER_SIZE 256

size_t count_characters(const char *str, size_t max_len)
{
    size_t count = 0;

    if (str == NULL)
    {
        return 0;
    }

    while (count < max_len && str[count] != '\0')
    {
        count++;
    }

    return count;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t length;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    buffer[strcspn(buffer, "\n")] = '\0';

    length = count_characters(buffer, sizeof(buffer));

    printf("Total characters: %zu\n", length);

    return 0;
}