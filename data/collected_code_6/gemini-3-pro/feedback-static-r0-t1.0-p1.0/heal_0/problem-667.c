#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    while (*str) {
        char ch = tolower((unsigned char)*str);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }
        str++;
    }
    return count;
}

int main(void) {
    const char *test_string = "Hello, World! Welcome to C programming.";
    
    int vowel_count = count_vowels(test_string);
    
    printf("The number of vowels is: %d\n", vowel_count);
    
    return 0;
}