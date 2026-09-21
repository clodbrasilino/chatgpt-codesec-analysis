#include <stdio.h>
#include <stdlib.h>

int is_vowel(char c) {
    switch (c) {
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            return 1;
        default:
            return 0;
    }
}

void reverse_vowels(char *s) {
    if (s == NULL || *s == '\0') {
        return;
    }

    char *left = s;
    char *right = s;

    while (*right != '\0') {
        right++;
    }
    right--;

    while (left < right) {
        if (!is_vowel(*left)) {
            left++;
        } else if (!is_vowel(*right)) {
            right--;
        } else {
            char temp = *left;
            *left = *right;
            *right = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    char str1[] = "hello";
    char str2[] = "programming";
    char str3[] = "AEIOUaeiou";
    char str4[] = "";

    reverse_vowels(str1);
    printf("%s\n", str1);

    reverse_vowels(str2);
    printf("%s\n", str2);

    reverse_vowels(str3);
    printf("%s\n", str3);

    reverse_vowels(str4);
    printf("%s\n", str4);

    return 0;
}