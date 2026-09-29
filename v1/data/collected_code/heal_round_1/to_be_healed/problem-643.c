#include <stdio.h>
#include <string.h>

int containsZ(char *word) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'word[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int length = strlen(word);
    if (length < 3) {
        return 0;
    }
    for (int i = 1; i < length - 1; i++) {
        if (word[i] == 'z') {
            return 1;
        }
    }
    return 0;
}

int main() {
    char word1[] = "zebra";
    char word2[] = "aztec";
    char word3[] = "blizzard";
    
    printf("%s: %s\n", word1, containsZ(word1) ? "Match" : "No match");
    printf("%s: %s\n", word2, containsZ(word2) ? "Match" : "No match");
    printf("%s: %s\n", word3, containsZ(word3) ? "Match" : "No match");
    
    return 0;
}