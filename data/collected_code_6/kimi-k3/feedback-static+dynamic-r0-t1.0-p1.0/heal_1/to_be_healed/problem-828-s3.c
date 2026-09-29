#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void count_characters(const char *str, int *alphabets, int *digits, int *special)
{
    int i;
    int len;
    
    *alphabets = 0;
    *digits = 0;
    *special = 0;
    
    if (str == NULL)
    {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    
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
    char str[256];
    int alphabets = 0;
    int digits = 0;
    int special = 0;
    
    printf("Enter a string: ");
    
    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    str[strcspn(str, "\n")] = '\0';
    
    count_characters(str, &alphabets, &digits, &special);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);
    
    return EXIT_SUCCESS;
}