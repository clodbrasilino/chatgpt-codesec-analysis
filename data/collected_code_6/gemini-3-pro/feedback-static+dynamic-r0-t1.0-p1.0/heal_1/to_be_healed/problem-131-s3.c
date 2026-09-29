#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_vowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
        return 1;
    }
    return 0;
}

void reverse_vowels(char *s) {
    if (s == NULL) {
        return;
    }

    int left = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int right = strlen(s) - 1;

    while (left < right) {
        if (!is_vowel(s[left])) {
            left++;
            continue;
        }
        if (!is_vowel(s[right])) {
            right--;
            continue;
        }

        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;

        left++;
        right--;
    }
}

int main(void) {
    char str1[] = "hello";
    char str2[] = "leetcode";

    reverse_vowels(str1);
    printf("%s\n", str1);

    reverse_vowels(str2);
    printf("%s\n", str2);

    return 0;
}