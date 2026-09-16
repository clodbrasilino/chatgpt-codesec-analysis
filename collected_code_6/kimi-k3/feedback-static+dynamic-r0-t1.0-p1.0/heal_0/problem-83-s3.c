#include <stdio.h>
#include <string.h>

char sum_string_chars(const char *str)
{
    int sum = 0;
    size_t i;
    
    if (str == NULL) {
        return '\0';
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        sum += (unsigned char)str[i];
    }
    
    return (char)(sum % 256);
}

int main(void)
{
    const char *test1 = "hello";
    const char *test2 = "abc";
    const char *test3 = "";
    
    printf("Sum of '%s': %d (char: %c)\n", test1, (unsigned char)sum_string_chars(test1), sum_string_chars(test1));
    printf("Sum of '%s': %d (char: %c)\n", test2, (unsigned char)sum_string_chars(test2), sum_string_chars(test2));
    printf("Sum of empty string: %d\n", (unsigned char)sum_string_chars(test3));
    
    return 0;
}