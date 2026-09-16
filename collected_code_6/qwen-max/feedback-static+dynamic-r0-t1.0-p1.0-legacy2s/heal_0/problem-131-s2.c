#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void reverse_vowels(char *str) {
    int len = strlen(str);
    int left = 0, right = len - 1;

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
    reverse_vowels(str);
    printf("%s\n", str);
    return 0;
}