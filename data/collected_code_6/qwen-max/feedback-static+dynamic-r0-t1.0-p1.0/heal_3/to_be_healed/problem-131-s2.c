#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

int is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void reverse_vowels(char *s, size_t len) {
    int64_t i, j;
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    reverse_vowels(str, strlen(str));
    printf("%s\n", str);
    return 0;
}