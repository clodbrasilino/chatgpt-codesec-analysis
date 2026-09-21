#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool starts_with_vowel_ae(const char *word)
{
    if (word == NULL || word[0] == '\0')
    {
        return false;
    }
    char first_char = tolower((unsigned char)word[0]);
    return (first_char == 'a' || first_char == 'e');
}

void find_words_starting_with_ae(const char *str)
{
    if (str == NULL)
    {
        fprintf(stderr, "Error: Input string is NULL\n");
        return;
    }

    size_t len = strnlen(str, 4096);
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

    snprintf(buffer, len + 1, "%s", str);
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
    char *input = NULL;
    size_t input_size = 0;
    ssize_t chars_read;

    printf("Enter a string: ");
    
    chars_read = getline(&input, &input_size, stdin);
    if (chars_read == -1)
    {
        fprintf(stderr, "Error: Failed to read input\n");
        free(input);
        return 1;
    }

    if (chars_read > 0 && input[chars_read - 1] == '\n')
    {
        input[chars_read - 1] = '\0';
    }

    find_words_starting_with_ae(input);

    free(input);
    return 0;
}