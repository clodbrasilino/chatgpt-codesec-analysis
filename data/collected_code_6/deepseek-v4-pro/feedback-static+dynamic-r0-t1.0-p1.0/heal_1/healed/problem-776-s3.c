#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int count_chars_with_vowel_neighbors(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    int i = 1;
    char prev, curr, next;
    
    if (str[0] == '\0' || str[1] == '\0') {
        return 0;
    }
    
    prev = str[0];
    curr = str[1];
    next = str[2];
    
    while (curr != '\0') {
        if (next != '\0' && isalpha(curr)) {
            if (is_vowel(prev) && is_vowel(next)) {
                count++;
            }
        }
        
        prev = curr;
        curr = next;
        if (next != '\0') {
            i++;
            next = str[i];
        }
    }
    
    return count;
}

int main(void) {
    char str1[] = "cat";
    char str2[] = "hello";
    char str3[] = "education";
    char str4[] = "a test string";
    char str5[] = "";
    
    printf("Count in \"%s\": %d\n", str1, count_chars_with_vowel_neighbors(str1));
    printf("Count in \"%s\": %d\n", str2, count_chars_with_vowel_neighbors(str2));
    printf("Count in \"%s\": %d\n", str3, count_chars_with_vowel_neighbors(str3));
    printf("Count in \"%s\": %d\n", str4, count_chars_with_vowel_neighbors(str4));
    printf("Count in \"%s\": %d\n", str5, count_chars_with_vowel_neighbors(str5));
    
    return 0;
}