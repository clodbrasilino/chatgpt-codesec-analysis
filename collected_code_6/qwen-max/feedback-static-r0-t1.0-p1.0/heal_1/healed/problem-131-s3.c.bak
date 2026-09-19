#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_vowel(char c) {
    const char vowels[] = "aeiouAEIOU";
    for (int i = 0; i < 10; ++i) {
        if (vowels[i] == c) {
            return true;
        }
    }
    return false;
}

void reverse_vowels(char *s) {
    int start = 0;
    int end = strlen(s) - 1;
    while (start < end) {
        if (!is_vowel(s[start])) {
            start++;
        } else if (!is_vowel(s[end])) {
            end--;
        } else {
            char temp = s[start];
            s[start] = s[end];
            s[end] = temp;
            start++;
            end--;
        }
    }
}

int main() {
    char str[] = "hello world";
    reverse_vowels(str);
    printf("%s\n", str);
    return 0;
}