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
    char str[257];
    int alphabets = 0;
    int digits = 0;
    int special = 0;
    size_t len;
    int ch;
    int too_long = 0;
    
    printf("Enter a string: ");
    
    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    str[sizeof(str) - 1] = '\0';
    len = strnlen(str, sizeof(str));
    
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
        len--;
    }
    else if (len == sizeof(str) - 1)
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            too_long = 1;
        }
        
        if (too_long)
        {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }
    
    count_characters(str, len, &alphabets, &digits, &special);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);
    
    return EXIT_SUCCESS;
}