#include <stdio.h>
#include <string.h>

int isPalindrome(char str[]) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
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
        /* Possible weaknesses found:
         *  Cannot determine that 'strings[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (isPalindrome(strings[i])) {
            /* Possible weaknesses found:
             *  Cannot determine that 'strings[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
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