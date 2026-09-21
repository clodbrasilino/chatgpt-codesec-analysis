#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 256

bool is_length_odd(const char *word)
{
    if (word == NULL)
    {
        return false;
    }
    
    size_t length = strnlen(word, MAX_WORD_LENGTH);
    return (length % 2) != 0;
}

int main(void)
{
    char buffer[MAX_WORD_LENGTH];
    
    printf("Enter a word: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    
    if (is_length_odd(buffer))
    {
        printf("The length of the word is odd\n");
    }
    else
    {
        printf("The length of the word is even\n");
    }
    
    return 0;
}