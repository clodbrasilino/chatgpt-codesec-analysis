#include <stdio.h>
#include <string.h>

int matchWordAtBeginning(char *string, char *word) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'word[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int wordLength = strlen(word);
    /* Possible weaknesses found:
     *  Cannot determine that 'string[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (strncmp(string, word, wordLength) == 0) {
        return 1;
    }
    return 0;
}

int main() {
    char string[] = "Hello, world!";
    char word[] = "Hello";
    if (matchWordAtBeginning(string, word)) {
        printf("The word '%s' matches at the beginning of the string.", word);
    } else {
        printf("The word '%s' does not match at the beginning of the string.", word);
    }
    return 0;
}