#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 1024

static size_t safe_strlen(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL)
    {
        return 0;
    }

    for (i = 0; i < max_len; i++)
    {
        if (str[i] == '\0')
        {
            return i;
        }
    }

    return max_len;
}

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

int reverse_words(char *str, size_t size)
{
    size_t len;
    size_t word_start;
    size_t i;

    if (str == NULL || size == 0)
    {
        return -1;
    }

    len = safe_strlen(str, size);
    if (len >= size)
    {
        return -1;
    }
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
    char input[INPUT_BUFFER_SIZE];
    char *work;
    size_t len;
    size_t work_size;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    int written;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    len = safe_strlen(input, sizeof(input));

    if (len == sizeof(input) - 1 && input[len - 1] != '\n')
    {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        fprintf(stderr, "Input exceeds maximum allowed length.\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
        len--;
    }

    work_size = len + 1;
    work = malloc(work_size);
    if (work == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    written = snprintf(work, work_size, "%s", input);
    if (written < 0 || (size_t)written >= work_size)
    {
        fprintf(stderr, "Failed to copy input.\n");
        free(work);
        return EXIT_FAILURE;
    }

    if (reverse_words(work, work_size) != 0)
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