#include <stdio.h>
#include <string.h>

void searchStrings(const char *string, const char *searchWord) {
    if (string == NULL || *string == '\0' || searchWord == NULL || *searchWord == '\0') {
        return;
    }
    
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t stringLen = strlen(string);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t wordLen = strlen(searchWord);
    
    if (wordLen > stringLen) {
        return;
    }

    for (size_t i = 0; i <= stringLen - wordLen; i++) {
        int match = 1;
        for (size_t j = 0; j < wordLen; j++) {
            if (string[i + j] != searchWord[j]) {
                match = 0;
                break;
            }
        }

        if (match) {
            printf("Found at index %lu\n", i);
        }
    }
}

int main() {
    char string[] = "This is a sample string to search";
    char searchWord[] = "sample";

    searchStrings(string, searchWord);

    return 0;
}