#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

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
    char *input = NULL;
    size_t capacity = 0;
    ssize_t nread;
    size_t len;

    printf("Enter a string: ");
    nread = getline(&input, &capacity, stdin);
    if (nread < 0)
    {
        fprintf(stderr, "Failed to read input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    len = (size_t)nread;
    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
        len--;
    }

    if (reverse_words(input, len + 1) != 0)
    {
        fprintf(stderr, "Failed to reverse words.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Reversed words: %s\n", input);

    free(input);
    input = NULL;

    return EXIT_SUCCESS;
}