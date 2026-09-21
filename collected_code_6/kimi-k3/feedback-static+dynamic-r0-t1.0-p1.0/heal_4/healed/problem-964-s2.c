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