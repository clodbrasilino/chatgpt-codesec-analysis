#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 100

void removeWord(char* words[], int* size, char* word) {
    int i;
    for(i = 0; i < *size; i++) {
        /* Possible weaknesses found:
         *  use of possibly-NULL '*words_29(D) + _2' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
         */
        if(strcmp(words[i], word) == 0) {
            free(words[i]);
            words[i] = words[*size - 1];
            (*size)--;
            i--;
        }
    }
}

int main() {
    int size = 5;
    char* words[MAX_WORDS] = {"Hello", "World", "I", "am", "here"};
    char word[MAX_WORD_LENGTH] = "here";

    for(int i = 0; i < size; i++) {
        words[i] = strdup(words[i]);
    }

    removeWord(words, &size, word);

    for(int i = 0; i < size; i++) {
        printf("%s ", words[i]);
        free(words[i]);
    }

    return 0;
}