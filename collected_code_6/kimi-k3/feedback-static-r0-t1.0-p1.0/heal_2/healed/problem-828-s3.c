#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void count_characters(const char *str, size_t max_len, int *alphabets, int *digits, int *special)
{
    size_t i;
    size_t len;
    
    *alphabets = 0;
    *digits = 0;
    *special = 0;
    
    if (str == NULL)
    {
        return;
    }
    
    len = strnlen(str, max_len);
    
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
    
    str[sizeof(str) - 1] = '\0';
    str[strcspn(str, "\n")] = '\0';
    
    count_characters(str, sizeof(str), &alphabets, &digits, &special);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);
    
    return EXIT_SUCCESS;
}