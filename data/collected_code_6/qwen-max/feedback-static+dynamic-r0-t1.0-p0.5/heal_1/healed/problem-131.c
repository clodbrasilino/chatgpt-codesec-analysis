#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_vowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void reverse_vowels(char *str, size_t len) {
    int left = 0;
    int right = len - 1;

    while (left < right) {
        if (!is_vowel(str[left])) {
            left++;
        } else if (!is_vowel(str[right])) {
            right--;
        } else {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;
            right--;
        }
    }
}

int main() {
    char str[] = "hello world";
    size_t len = sizeof(str) / sizeof(str[0]) - 1;
    reverse_vowels(str, len);
    printf("%s\n", str);
    return 0;
}