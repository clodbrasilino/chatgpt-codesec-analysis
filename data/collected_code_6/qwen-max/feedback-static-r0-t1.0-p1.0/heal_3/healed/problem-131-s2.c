#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void reverse_vowels(char *s, size_t len) {
    int i, j;
    for (i = 0, j = len - 1; i < j; ) {
        while (i < j && !is_vowel(s[i])) i++;
        while (i < j && !is_vowel(s[j])) j--;
        if (i < j) {
            char tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
            i++;
            j--;
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