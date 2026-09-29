#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_odd_length(const char *word, size_t max_len)
{
    size_t length;

    if (word == NULL || max_len == 0)
    {
        return false;
    }

    length = strnlen(word, max_len);
    return (length % 2) != 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];

    printf("Enter a word: ");

    if (fgets(word, sizeof(word), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    word[strcspn(word, "\n")] = '\0';

    if (is_odd_length(word, sizeof(word)))
    {
        printf("The length of the word is odd.\n");
    }
    else
    {
        printf("The length of the word is even.\n");
    }

    return 0;
}