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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
    if (len < 3) {
        return 0;
    }
    
    char prev = str[0];
    char curr = str[1];
    
    for (size_t i = 2; i < len; i++) {
        char next = str[i];
        
        if (isalpha((unsigned char)curr)) {
            if (is_vowel(prev) && is_vowel(next)) {
                count++;
            }
        }
        prev = curr;
        curr = next;
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