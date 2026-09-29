#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void count_characters(const char *str, size_t len, int *alphabets, int *digits, int *special)
{
    size_t i;
    
    *alphabets = 0;
    *digits = 0;
    *special = 0;
    
    if (str == NULL)
    {
        return;
    }
    
    for (i = 0; i < len; i++)
    {
        if (isalpha((unsigned char)str[i]))
        {
            (*alphabets)++;
        }
        else if (isdigit((unsigned char)str[i]))
        {
            (*digits)++;
        }
        else if (str[i] != ' ' && str[i] != '\0')
        {
            (*special)++;
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[257];
    int alphabets = 0;
    int digits = 0;
    int special = 0;
    size_t len;
    
    printf("Enter a string: ");
    
    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (strchr(str, '\n') == NULL && !feof(stdin))
    {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    len = strcspn(str, "\n");
    str[len] = '\0';
    
    count_characters(str, len, &alphabets, &digits, &special);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);
    
    return EXIT_SUCCESS;
}