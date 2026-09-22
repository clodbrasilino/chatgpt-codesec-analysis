#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_vowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
        return 1;
    }
    return 0;
}

void reverse_vowels(char *s, size_t max_len) {
    if (s == NULL || max_len == 0) {
        return;
    }

    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return;
    }

    int left = 0;
    int right = len - 1;

    while (left < right) {
        if (!is_vowel(s[left])) {
            left++;
            continue;
        }
        if (!is_vowel(s[right])) {
            right--;
            continue;
        }

        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;

        left++;
        right--;
    }
}

int main(void) {
    char str1[] = "hello";
    char str2[] = "leetcode";

    reverse_vowels(str1, sizeof(str1));
    printf("%s\n", str1);

    reverse_vowels(str2, sizeof(str2));
    printf("%s\n", str2);

    return 0;
}