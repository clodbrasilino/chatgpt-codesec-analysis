#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
        int clear_status = 0;
        
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
        {
            clear_status = 1;
        }
        
        if (c == EOF && clear_status == 0)
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