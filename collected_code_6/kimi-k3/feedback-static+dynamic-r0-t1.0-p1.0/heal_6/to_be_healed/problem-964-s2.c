#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 1024

bool is_length_even(const char *word, size_t max_len)
{
    if (word == NULL || max_len == 0)
    {
        return false;
    }
    size_t len = strnlen(word, max_len);
    return (len % 2) == 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LENGTH];

    printf("Enter a word: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    else if (len == sizeof(buffer) - 1)
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }

    if (is_length_even(buffer, sizeof(buffer)))
    {
        printf("The length of the word is even.\n");
    }
    else
    {
        printf("The length of the word is odd.\n");
    }

    return EXIT_SUCCESS;
}