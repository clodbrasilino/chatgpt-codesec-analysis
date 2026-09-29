#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void reverse_segment(char *str, size_t start, size_t end)
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
    size_t word_start;
    size_t i;

    if (str == NULL || max_len == 0)
    {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == 0)
    {
        return 0;
    }

    reverse_segment(str, 0, len - 1);

    word_start = 0;
    for (i = 0; i <= len; i++)
    {
        if (i == len || isspace((unsigned char)str[i]))
        {
            if (i > word_start)
            {
                reverse_segment(str, word_start, i - 1);
            }
            word_start = i + 1;
        }
    }

    return 0;
}

int main(void)
{
    char input[1024];
    char *work;
    size_t len;
    int written;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));

    if (len == sizeof(input) - 1 && input[len - 1] != '\n')
    {
        fprintf(stderr, "Input too long.\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
        len--;
    }

    work = malloc(len + 1);
    if (work == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    written = snprintf(work, len + 1, "%s", input);
    if (written < 0 || (size_t)written >= len + 1)
    {
        fprintf(stderr, "Failed to copy input.\n");
        free(work);
        return EXIT_FAILURE;
    }

    if (reverse_words(work, len + 1) != 0)
    {
        fprintf(stderr, "Failed to reverse words.\n");
        free(work);
        return EXIT_FAILURE;
    }

    printf("Reversed words: %s\n", work);

    free(work);
    work = NULL;

    return EXIT_SUCCESS;
}