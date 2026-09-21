#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_odd_length(const char *word, size_t max_len)
{
    if (word == NULL || max_len == 0)
    {
        return false;
    }
    
    size_t len = strnlen(word, max_len);
    if (len == max_len)
    {
        return false;
    }
    
    return (len % 2) != 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];
    
    if (fgets(word, sizeof(word), stdin) != NULL)
    {
        size_t len = strnlen(word, sizeof(word));
        
        if (len == sizeof(word) && word[len - 1] != '\n')
        {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
        }
        else if (len > 0 && word[len - 1] == '\n')
        {
            word[len - 1] = '\0';
        }
        
        if (is_odd_length(word, sizeof(word)))
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