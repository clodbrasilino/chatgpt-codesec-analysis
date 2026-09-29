#include <stdio.h>
#include <stddef.h>

int isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void reverseVowels(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    size_t len = 0;
    while (len < size && str[len] != '\0') {
        len++;
    }
    if (len == 0) {
        return;
    }
    size_t left = 0;
    size_t right = len - 1;
    while (left < right) {
        while (left < right && !isVowel(str[left])) {
            left++;
        }
        while (left < right && !isVowel(str[right])) {
            right--;
        }
        if (left < right) {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    char text[] = "Hello, World!";
    reverseVowels(text, sizeof(text));
    printf("%s\n", text);
    return 0;
}