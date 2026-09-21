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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    if (len < 3) {
        return 0;
    }
    
    int count = 0;
    
    for (int i = 1; i < len - 1; i++) {
        if (is_vowel(str[i - 1]) && is_vowel(str[i + 1])) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    const char *test_strings[] = {
        "hello world",
        "a test string with vowels",
        "abcdefg",
        "aeiou",
        "",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("String: \"%s\" -> Count: %d\n", 
               test_strings[i], 
               count_chars_with_vowel_neighbors(test_strings[i]));
    }
    
    return 0;
}