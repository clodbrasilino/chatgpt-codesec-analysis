#include <stdio.h>
#include <string.h>

int isPalindrome(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

void findPalindromes(char* strings[], int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        if (isPalindrome(strings[i])) {
            printf("%s is a palindrome.\n", strings[i]);
        }
    }
}

int main() {
    char* strings[] = {"hello", "level", "world", "deed"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);

    findPalindromes(strings, numStrings);

    return 0;
}