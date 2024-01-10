#include <stdio.h>
#include <string.h>

int isPalindrome(const char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

void findPalindromes(const char* const *strings, size_t numStrings) {
    for (size_t i = 0; i < numStrings; i++) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if (isPalindrome(strings[i], strlen(strings[i]))) {
            printf("%s is a palindrome.\n", strings[i]);
        }
    }
}

int main() {
    const char* strings[] = {"hello", "level", "world", "deed"};
    size_t numStrings = sizeof(strings) / sizeof(strings[0]);

    findPalindromes(strings, numStrings);

    return 0;
}
