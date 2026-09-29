#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_range(char *str, size_t start, size_t end)
{
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int reverse_words(char *str)
{
    size_t len;
    size_t start;
    size_t i;

    if (str == NULL)
    {
        return -1;
    }

    len = strlen(str);
    if (len == 0)
    {
        return 0;
    }

    reverse_range(str, 0, len - 1);

    start = 0;
    for (i = 0; i <= len; i++)
    {
        if (str[i] == ' ' || str[i] == '\0')
        {
            if (i > start)
            {
                reverse_range(str, start, i - 1);
            }
            start = i + 1;
        }
    }

    return 0;
}

int main(void)
{
    const char *input = "The quick brown fox jumps over the lazy dog";
    size_t len = strlen(input);
    char *buffer = malloc(len + 1);

    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, input, len + 1);

    printf("Original: %s\n", buffer);

    if (reverse_words(buffer) != 0)
    {
        fprintf(stderr, "Failed to reverse words\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Reversed: %s\n", buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}