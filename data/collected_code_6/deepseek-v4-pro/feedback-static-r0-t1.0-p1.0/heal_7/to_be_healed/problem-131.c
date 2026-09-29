#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void reverse_vowels(char *str, size_t buffer_size) {
    size_t len;
    size_t left = 0;
    size_t right;
    char temp;
    
    if (str == NULL || buffer_size == 0) {
        return;
    }
    
    len = safe_strlen(str, buffer_size);
    if (len == 0) {
        return;
    }
    right = len - 1;
    
    while (left < right) {
        while (left < right && !is_vowel(str[left])) {
            left++;
        }
        while (left < right && !is_vowel(str[right])) {
            right--;
        }
        
        if (left < right) {
            temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[16] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[16] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str3[16] = {0};
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(str1, "hello", sizeof(str1) - 1);
    str1[sizeof(str1) - 1] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(str2, "leetcode", sizeof(str2) - 1);
    str2[sizeof(str2) - 1] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(str3, "aA", sizeof(str3) - 1);
    str3[sizeof(str3) - 1] = '\0';
    
    reverse_vowels(str1, sizeof(str1));
    reverse_vowels(str2, sizeof(str2));
    reverse_vowels(str3, sizeof(str3));
    
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    
    return 0;
}