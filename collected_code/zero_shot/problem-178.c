#include <stdio.h>
#include <string.h>

void searchStrings(char *string, char *searchWord) {
    int i, j, match;
    int stringLen = strlen(string);
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