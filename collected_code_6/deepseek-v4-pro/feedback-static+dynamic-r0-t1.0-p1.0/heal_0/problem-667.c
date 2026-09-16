#include <stdio.h>
#include <ctype.h>

int count_vowels(const char *str) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    
    while (*str != '\0') {
        char c = tolower((unsigned char)*str);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        str++;
    }
    
    return count;
}

int main(void) {
    const char *test_string = "Hello World";
    int vowel_count = count_vowels(test_string);
    
    printf("String: %s\n", test_string);
    printf("Number of vowels: %d\n", vowel_count);
    
    return 0;
}