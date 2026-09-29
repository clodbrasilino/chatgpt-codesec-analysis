#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    char vowels[] = "aeiouAEIOU";
    for (int i = 0; i < 10; i++) {
        if (c == vowels[i]) return 1;
    }
    return 0;
}

void reverse_vowels(char *str) {
    int len = strlen(str);
    int start = 0, end = len - 1;

    while (start < end) {
        if (!is_vowel(str[start])) {
            start++;
        } else if (!is_vowel(str[end])) {
            end--;
        } else {
            char temp = str[start];
            str[start] = str[end];
            str[end] = temp;
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