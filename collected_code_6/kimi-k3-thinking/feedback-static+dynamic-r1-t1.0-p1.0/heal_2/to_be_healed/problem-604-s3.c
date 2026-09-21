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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[65536];

    while (fgets(input, sizeof(input), stdin) != NULL)
    {
        input[strcspn(input, "\r\n")] = '\0';

        char *reversed = reverse_words(input);
        if (reversed == NULL)
        {
            fprintf(stderr, "Error: failed to reverse words\n");
            return EXIT_FAILURE;
        }

        fputs(reversed, stdout);
        putchar('\n');

        free(reversed);
    }

    return EXIT_SUCCESS;
}