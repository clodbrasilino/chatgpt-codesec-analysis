#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int count_chars_with_vowel_neighbors(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    int i = 0;
    
    if (str[0] == '\0' || str[1] == '\0') {
        return 0;
    }
    
    i = 1;
    while (str[i] != '\0' && str[i + 1] != '\0') {
        if (is_vowel(str[i - 1]) && is_vowel(str[i + 1])) {
            count++;
        }
        i++;
    }
    
    return count;
}

int main(void) {
    const char *str1 = "hello";
    printf("%d\n", count_chars_with_vowel_neighbors(str1));
    
    const char *str2 = "beautiful";
    printf("%d\n", count_chars_with_vowel_neighbors(str2));
    
    const char *str3 = "aeiou";
    printf("%d\n", count_chars_with_vowel_neighbors(str3));
    
    const char *str4 = "cat";
    printf("%d\n", count_chars_with_vowel_neighbors(str4));
    
    return 0;
}