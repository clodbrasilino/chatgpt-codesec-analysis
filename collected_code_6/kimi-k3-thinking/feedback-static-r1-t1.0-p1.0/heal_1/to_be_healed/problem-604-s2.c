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

int reverse_words(char *str)
{
    size_t len;
    size_t word_start;
    size_t i;

    if (str == NULL)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0)
    {
        return 0;
    }

    reverse_segment(str, 0, len - 1);

    word_start = 0;
    for (i = 0; i <= len; i++)
    {
        if (str[i] == '\0' || isspace((unsigned char)str[i]))
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    char *work;
    size_t len;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
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
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(work, input, len + 1);

    if (reverse_words(work) != 0)
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