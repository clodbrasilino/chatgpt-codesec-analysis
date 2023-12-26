#include <stdio.h>
#include <string.h>

void searchStrings(char *string, char *searchWord) {
    int i, j, match;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'string[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int stringLen = strlen(string);
    /* Possible weaknesses found:
     *  Cannot determine that 'searchWord[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int wordLen = strlen(searchWord);

    for (i = 0; i <= stringLen - wordLen; i++) {
        match = 1;
        for (j = 0; j < wordLen; j++) {
            if (string[i + j] != searchWord[j]) {
                match = 0;
                break;
            }
        }

        if (match == 1) {
            printf("Found at index %d\n", i);
        }
    }
}

int main() {
    char string[] = "This is a sample string to search";
    char searchWord[] = "sample";
    
    searchStrings(string, searchWord);

    return 0;
}