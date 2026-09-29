#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_vowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void reverse_vowels(char *s, size_t len) {
    if (s == NULL) {
        return;
    }
    
    size_t left = 0;
    size_t right = len;
    
    if (right == 0) {
        return;
    }
    
    right--;
    
    while (left < right) {
        if (!is_vowel(s[left])) {
            left++;
        } else if (!is_vowel(s[right])) {
            right--;
        } else {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    char str1[] = "hello world";
    char str2[] = "programming";
    char str3[] = "AEIOU";
    
    printf("Original: %s\n", str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    reverse_vowels(str1, strlen(str1));
    printf("Reversed: %s\n", str1);
    
    printf("Original: %s\n", str2);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    reverse_vowels(str2, strlen(str2));
    printf("Reversed: %s\n", str2);
    
    printf("Original: %s\n", str3);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    reverse_vowels(str3, strlen(str3));
    printf("Reversed: %s\n", str3);
    
    return 0;
}