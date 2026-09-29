#include <stdio.h>
#include <string.h>
#include <stddef.h>

size_t count_characters(const char *str, size_t max_len)
{
    if (str == NULL)
    {
        return 0;
    }
    return strnlen(str, max_len);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    printf("Total characters: %zu\n", count_characters(buffer, sizeof(buffer)));
    
    return 0;
}