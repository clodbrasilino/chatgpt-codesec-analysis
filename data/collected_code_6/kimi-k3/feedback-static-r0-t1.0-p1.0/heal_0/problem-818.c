#include <stdio.h>
#include <stddef.h>

size_t count_lowercase(const char *str)
{
    size_t count = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            count++;
        }
        str++;
    }
    
    return count;
}

int main(void)
{
    const char *test_string = "Hello World Example";
    size_t result;
    
    result = count_lowercase(test_string);
    printf("Lowercase letters: %zu\n", result);
    
    return 0;
}