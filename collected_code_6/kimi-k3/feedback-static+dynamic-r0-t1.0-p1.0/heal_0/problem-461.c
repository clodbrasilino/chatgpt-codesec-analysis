#include <stdio.h>
#include <string.h>

int count_uppercase(const char *str)
{
    int count = 0;
    if (str == NULL)
    {
        return 0;
    }
    while (*str != '\0')
    {
        if (*str >= 'A' && *str <= 'Z')
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

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    result = count_uppercase(buffer);
    printf("Number of uppercase characters: %d\n", result);

    return 0;
}