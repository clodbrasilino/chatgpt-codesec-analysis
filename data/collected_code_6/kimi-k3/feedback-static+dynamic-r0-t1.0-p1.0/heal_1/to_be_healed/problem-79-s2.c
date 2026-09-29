#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_odd_length(const char *word)
{
    if (word == NULL)
    {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return (strlen(word) % 2) != 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];
    
    if (fgets(word, sizeof(word), stdin) != NULL)
    {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n')
        {
            word[len - 1] = '\0';
        }
        
        if (is_odd_length(word))
        {
            printf("Odd length\n");
        }
        else
        {
            printf("Even length\n");
        }
    }
    
    return 0;
}