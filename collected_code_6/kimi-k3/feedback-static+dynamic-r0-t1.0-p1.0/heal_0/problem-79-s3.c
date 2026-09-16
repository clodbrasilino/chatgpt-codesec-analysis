#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_length_odd(const char *word)
{
    if (word == NULL)
    {
        return false;
    }
    
    size_t length = strlen(word);
    return (length % 2) != 0;
}

int main(void)
{
    char buffer[256];
    
    printf("Enter a word: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strlen(buffer);
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