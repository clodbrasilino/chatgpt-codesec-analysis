#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_length_odd(const char *word)
{
    if (word == NULL)
    {
        return false;
    }
    
    size_t length = strnlen(word, 256);
    return (length % 2) != 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
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