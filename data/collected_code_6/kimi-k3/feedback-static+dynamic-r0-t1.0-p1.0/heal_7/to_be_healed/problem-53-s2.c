#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_first_last_equal(const char *str, size_t max_len)
{
    size_t len;
    
    if (str == NULL || max_len == 0)
    {
        return false;
    }
    
    len = strnlen(str, max_len);
    
    if (len == 0 || len >= max_len)
    {
        return false;
    }
    
    return str[0] == str[len - 1];
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n')
    {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        fprintf(stderr, "Input too long\n");
        return 1;
    }
    
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    }
    
    if (check_first_last_equal(buffer, sizeof(buffer)))
    {
        printf("First and last characters are equal\n");
    }
    else
    {
        printf("First and last characters are not equal\n");
    }
    
    return 0;
}