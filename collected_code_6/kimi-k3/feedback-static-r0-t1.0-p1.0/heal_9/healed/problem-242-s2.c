#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INPUT_SIZE 256

int count_characters(const char *str)
{
    if (str == NULL)
    {
        return -1;
    }
    
    int count = 0;
    while (count < MAX_INPUT_SIZE && str[count] != '\0')
    {
        count++;
    }
    return count;
}

int main(void)
{
    char input[MAX_INPUT_SIZE];
    
    printf("Enter a string: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(input, sizeof(input));
    
    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
    }
    else if (len == sizeof(input) - 1)
    {
        int c;
        bool cleared = false;
        
        while ((c = getchar()) != '\n' && c != EOF)
        {
            cleared = true;
        }
        
        if (c == EOF && !cleared)
        {
            fprintf(stderr, "Error reading input\n");
            return 1;
        }
    }
    
    int result = count_characters(input);
    
    if (result >= 0)
    {
        printf("Total characters: %d\n", result);
    }
    else
    {
        fprintf(stderr, "Error counting characters\n");
        return 1;
    }
    
    return 0;
}