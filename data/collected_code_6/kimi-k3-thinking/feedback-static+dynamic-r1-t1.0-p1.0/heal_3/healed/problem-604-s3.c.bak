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

char *reverse_words(const char *str)
{
    size_t len;
    size_t word_start;
    size_t i;
    char *result;

    if (str == NULL)
    {
        return NULL;
    }

    len = strlen(str);
    result = malloc(len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    memcpy(result, str, len + 1);

    if (len > 0)
    {
        reverse_range(result, 0, len - 1);
    }

    word_start = 0;
    for (i = 0; i <= len; i++)
    {
        if (result[i] == ' ' || result[i] == '\0')
        {
            if (word_start < i)
            {
                reverse_range(result, word_start, i - 1);
            }
            word_start = i + 1;
        }
    }

    return result;
}

int main(int argc, const char *argv[])
{
    char input[4096];
    size_t used = 0;
    char *reversed;

    input[0] = '\0';

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            size_t remaining = sizeof(input) - 1 - used;
            if (i > 1 && remaining > 0)
            {
                input[used] = ' ';
                used++;
                remaining--;
            }
            size_t arg_len = strlen(argv[i]);
            if (arg_len > remaining)
            {
                arg_len = remaining;
            }
            memcpy(input + used, argv[i], arg_len);
            used += arg_len;
            input[used] = '\0';
        }
    }
    else
    {
        if (fgets(input, (int)sizeof(input), stdin) == NULL)
        {
            input[0] = '\0';
        }
        input[strcspn(input, "\r\n")] = '\0';
    }

    reversed = reverse_words(input);

    if (reversed == NULL)
    {
        fprintf(stderr, "Error: failed to reverse words\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", reversed);

    free(reversed);

    return EXIT_SUCCESS;
}