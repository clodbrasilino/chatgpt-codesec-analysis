#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

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

    size_t len = strlen(str);
    if (len == 0)
    {
        printf("No words found in the input string.\n");
        return;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *buffer = malloc(len + 1);
    if (buffer == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }

    strcpy(buffer, str);
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

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(buffer);
    buffer = NULL;
}

int main(void)
{
    char input[1024];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read input\n");
        return 1;
    }

    size_t input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n')
    {
        input[input_len - 1] = '\0';
    }

    find_words_starting_with_ae(input);

    return 0;
}