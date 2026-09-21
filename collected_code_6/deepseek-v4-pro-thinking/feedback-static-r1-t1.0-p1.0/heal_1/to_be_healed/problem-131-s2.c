#include <stdio.h>
#include <stddef.h>
#include <string.h>

char *reverseVowels(char *s) {
    if (s == NULL || *s == '\0') {
        return s;
    }
    const char *vowels = "aeiouAEIOU";
    char *left = s;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *right = s + strlen(s) - 1;
    while (left < right) {
        while (left < right && strchr(vowels, (unsigned char)*left) == NULL) {
            left++;
        }
        while (left < right && strchr(vowels, (unsigned char)*right) == NULL) {
            right--;
        }
        if (left < right) {
            char temp = *left;
            *left = *right;
            *right = temp;
            left++;
            right--;
        }
    }
    return s;
}

int main(void) {
    char str[] = "hello world";
    printf("%s\n", reverseVowels(str));
    return 0;
}