#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

bool starts_with_vowel_ae(const char *word)
{
    if (word == NULL || word[0] == '\0')
    {
        return false;
    }
    char first_char = tolower((unsigned char)word[0]);
    return (first_char == 'a' || first_char == 'e');
}

void find_words_starting_with_ae(const char *str, size_t max_len)
{
    if (str == NULL)
    {
        fprintf(stderr, "Error: Input string is NULL\n");
        return;
    }

    size_t len = strnlen(str, max_len);
    if (len == 0)
    {
        printf("No words found in the input string.\n");
        return;
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }

    strncpy(buffer, str, len);
    buffer[len] = '\0';
    
    char *token = strtok(buffer, " \t\n\r.,;:!?");
    bool found_any = false;

    printf("Words starting with 'a' or 'e':\n");
    while (token != NULL)
    {
        if (starts_with_vowel_ae(token))
        {
            printf("%s\n", token);
            found_any = true;
        }
        token = strtok(NULL, " \t\n\r.,;:!?");
    }

    if (!found_any)
    {
        printf("None found.\n");
    }

    free(buffer);
    buffer = NULL;
}

int main(void)
{
    char input[MAX_INPUT_SIZE];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read input\n");
        return 1;
    }

    size_t input_len = strnlen(input, sizeof(input));
    if (input_len > 0 && input[input_len - 1] == '\n')
    {
        input[input_len - 1] = '\0';
    }

    find_words_starting_with_ae(input, sizeof(input));

    return 0;
}