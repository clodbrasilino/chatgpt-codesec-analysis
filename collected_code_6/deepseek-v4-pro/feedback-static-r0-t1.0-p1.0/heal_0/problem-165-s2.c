#include <stdio.h>
#include <ctype.h>
#include <string.h>

int countAlphabetPositionMatches(const char *str) {
    if (str == NULL) {
        return -1;
    }
    
    int count = 0;
    int position = 1;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            char lower_char = tolower((unsigned char)str[i]);
            int char_position = lower_char - 'a' + 1;
            
            if (char_position == position) {
                count++;
            }
            position++;
        }
    }
    
    return count;
}

int main(void) {
    char str1[] = "AbC";
    char str2[] = "abcdefghijklmnopqrstuvwxyz";
    char str3[] = "test string";
    char str4[] = "hello world";
    
    printf("String: %s, Count: %d\n", str1, countAlphabetPositionMatches(str1));
    printf("String: %s, Count: %d\n", str2, countAlphabetPositionMatches(str2));
    printf("String: %s, Count: %d\n", str3, countAlphabetPositionMatches(str3));
    printf("String: %s, Count: %d\n", str4, countAlphabetPositionMatches(str4));
    
    return 0;
}