#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    const char vowels[] = "aeiouAEIOU";
    for (int i = 0; i < 10; i++) {
        if (c == vowels[i]) return 1;
    }
    return 0;
}

void reverse_vowels(char *str, size_t len) {
    int start = 0, end = len - 2;

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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len > 0) {
        reverse_vowels(str, len);
        printf("%s\n", str);
    }
    return 0;
}