#include <stdio.h>
#include <string.h>

void searchStrings(const char *string, const char *searchWord) {
    if (string == NULL || searchWord == NULL) {
        return;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int stringLen = strlen(string);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int wordLen = strlen(searchWord);

    if (wordLen > stringLen) {
        return;
    }

    for (int i = 0; i <= stringLen - wordLen; i++) {
        int match = 1;
        for (int j = 0; j < wordLen; j++) {
            if (string[i + j] != searchWord[j]) {
                match = 0;
                break;
            }
        }

        if (match) {
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