#include <stdio.h>

int is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void reverse_vowels(char *s, size_t len) {
    if (s == NULL || len == 0) {
        return;
    }
    size_t left = 0;
    size_t right = len - 1;
    while (left < right) {
        while (left < right && !is_vowel(s[left])) {
            left++;
        }
        while (left < right && !is_vowel(s[right])) {
            right--;
        }
        if (left < right) {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    char str1[] = "hello";
    char str2[] = "leetcode";
    reverse_vowels(str1, sizeof(str1) - 1);
    reverse_vowels(str2, sizeof(str2) - 1);
    printf("%s\n", str1);
    printf("%s\n", str2);
    return 0;
}