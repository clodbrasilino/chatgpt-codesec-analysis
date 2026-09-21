#include <stdio.h>
#include <string.h>

int isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void reverseVowels(char *str) {
    if (str == NULL) {
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
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
    reverseVowels(text);
    printf("%s\n", text);
    return 0;
}