#include <stdio.h>
#include <string.h>

void searchStrings(const char *string, const char *searchWord) {
    if (string == NULL || searchWord == NULL) {
        return;
    }

    size_t stringLen = strnlen(string, 1000);
    size_t wordLen = strnlen(searchWord, 1000);

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