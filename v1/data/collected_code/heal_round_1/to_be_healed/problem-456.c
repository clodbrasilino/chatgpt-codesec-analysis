#include <stdio.h>
#include <string.h>

void reverseStrings(char** strings, int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'strings[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        char* str = strings[i];
        /* Possible weaknesses found:
         *  Cannot determine that 'str' is initialized [premium-bughuntingUninit]
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        int len = strlen(str);
        for (int j = 0; j < len / 2; j++) {
            char temp = str[j];
            /* Possible weaknesses found:
             *  Cannot determine that 'str' is initialized [premium-bughuntingUninit]
             *  write to string literal [-Wanalyzer-write-to-string-literal]
             */
            str[j] = str[len - j - 1];
            /* Possible weaknesses found:
             *  write to string literal [-Wanalyzer-write-to-string-literal]
             */
            str[len - j - 1] = temp;
        }
    }
}

int main() {
    char* strings[] = {"hello", "world", "example"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);

    reverseStrings(strings, numStrings);
    for (int i = 0; i < numStrings; i++) {
        printf("%s\n", strings[i]);
    }
    
    return 0;
}