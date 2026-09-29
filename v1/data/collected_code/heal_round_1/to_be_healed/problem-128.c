#include <stdio.h>
#include <string.h>

void shortlistWords(char* words[], int numWords, int n) {
    printf("Shortlisted words longer than %d characters:\n", n);
    
    for (int i = 0; i < numWords; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'words[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if (strlen(words[i]) > n) {
            /* Possible weaknesses found:
             *  Cannot determine that 'words[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%s\n", words[i]);
        }
    }
}

int main() {
    char* words[] = {"apple", "banana", "carrot", "pineapple", "grape"};
    int numWords = sizeof(words) / sizeof(words[0]);
    int n = 6;
    
    shortlistWords(words, numWords, n);
    
    return 0;
}