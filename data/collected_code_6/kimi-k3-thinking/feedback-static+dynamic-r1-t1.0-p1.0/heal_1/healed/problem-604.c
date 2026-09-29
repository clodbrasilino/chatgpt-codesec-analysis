#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096

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

int reverse_words(char *str, size_t max_len)
{
    size_t len;
    size_t start;
    size_t i;

    if (str == NULL || max_len == 0)
    {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == max_len)
    {
        return -1;
    }

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
    size_t len;
    char *buffer;

    len = strnlen(input, MAX_INPUT_LENGTH);
    if (len == MAX_INPUT_LENGTH)
    {
        fprintf(stderr, "Input string is too long or not null-terminated\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(len + 1);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, input, len);
    buffer[len] = '\0';

    printf("Original: %s\n", buffer);

    if (reverse_words(buffer, len + 1) != 0)
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