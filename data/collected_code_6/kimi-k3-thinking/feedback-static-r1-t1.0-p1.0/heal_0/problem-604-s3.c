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
    if (str == NULL)
    {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    memcpy(result, str, len + 1);

    if (len > 0)
    {
        reverse_range(result, 0, len - 1);
    }

    size_t word_start = 0;
    for (size_t i = 0; i <= len; i++)
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

int main(void)
{
    const char *input = "The quick brown fox jumps over the lazy dog";
    char *reversed = reverse_words(input);

    if (reversed == NULL)
    {
        fprintf(stderr, "Error: failed to reverse words\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Reversed: %s\n", reversed);

    free(reversed);

    return EXIT_SUCCESS;
}